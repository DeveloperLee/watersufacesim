#version 400 core

//---------------------Uniforms--------------------------//

uniform ivec2 resolution;      // Screen resolution
uniform mat4 fragMVP;          // MVP matrix for handling camera rotation
uniform float currentTime;     // Current time in seconds
uniform float cloudThickness;  // Thinkness of the cloud
uniform float shadowHardness;  // Hardness of the shadow
uniform float wideAngle;       // Wide angle of the camera
uniform float camX;
uniform float camY;
uniform float bigwave;
uniform float smallwave;
uniform vec2 wavespeed;
uniform bool renderFog;        // True: render fog, False: doesn't render
uniform bool renderShadow;
uniform bool renderCloud;      // True: render cloud, False: doesn't render
uniform bool renderLens;
uniform bool renderSnow;
uniform bool renderRain;
uniform sampler2D noise_texture;     // Noise texture sampler
uniform sampler2D terrain_texture;   // Terrain texture sampler

//---------------------Parameters------------------------//

float march_steps = 150;
float diff = 0.;
float sparse = 0.995;
float waterOctaves = 8;
float terrainOctaves = 10;
float rainOctaves = 12;
float cloudOctaves = 100;
float march_far = 500.;

//---------------------Colors--------------------------//

vec3 skycolor       = vec3(.53, .807, .9215);
vec3 nightskycolor  = vec3(0.1, 0.2, 0.4);
vec3 watercolor   = vec3(0.2, 0.25, 0.3);
vec3 fogcolor    = vec3( 0.5, 0.5, 0.5);
vec3 suncolor   = vec3( 1.0, 0.9, 0.7 );
vec3 sunhazecolor = vec3(.77,.57,.432);
vec3 nightSuncolor = vec3(151., 153., 155.) / 255.;
vec3 darkcloud = vec3(.28, .28, .2);
vec3 reflskycolor = vec3(0.025, 0.10, 0.20);

//---------------------Movements------------------------//

float sunshift = sin(currentTime * .05);
vec2 cloudshift = vec2(currentTime) * vec2(70.,50.);
vec3 light = normalize( vec3(0.5, clamp(sunshift,-1.,.3),  0.5) );
mat2 fbm2Dmat2 = mat2(.4,-.3,.4,.3);
mat3 m = mat3( 0.00,  1.60,  1.20, -1.60,  0.72, -0.96, -1.20, -0.96,  1.28 );


struct Camera{

    vec3 pos; //Current position of the camera
    vec3 look; //Look vector
    vec3 u,v,w; //u,v,w coordinate of the camera
    mat3 trans;
};

out vec3 fragColor;   // Final output color for each pixel

// Hash function
float hash(float n)
{
    return fract(sin(n)*43758.5453123 + cos(n)*127.1);
}

float hash2(float n)
{
    return fract((1.0 + cos(n)) * 415.92653);
}

// 2d noise function
float noise(vec2 p)
{
    return texture(noise_texture,p/256.).x;
}

// trilinear interpolation for generating clouds
float noise(vec3 x)
{
    vec3 p  = floor(x);
    vec3 f  = smoothstep(0.0, 1.0, fract(x));
    float n = p.x + p.y*57.0 + 113.0*p.z;

    return mix(mix(mix( hash(n+  0.0), hash(n+  1.0),f.x),
               mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y),
               mix(mix( hash(n+113.0), hash(n+114.0),f.x),
               mix( hash(n+170.0), hash(n+171.0),f.x),f.y),f.z);
}

float starNoise(vec3 x)
{
    float xhash = hash2( x.x * 37.0 );
    float yhash = hash2( x.y * 57.0 );
    float zhash = hash2( x.z * 77.0 );
    return fract( xhash + yhash + zhash );
}

float fbm3D( vec3 p )
{
    float f = .5*noise( p );
    f += .25*noise( m * p);
    f += .125*noise( m * p);
    f += .0625*noise( m * p );
    return f;
}

float fbm2D( vec2 p )
{
    float f = .5*noise( p);
    f += .25*noise( fbm2Dmat2 * p * 4.);
    f += .125*noise( fbm2Dmat2 * p * 4.);
    f += .0625*noise( fbm2Dmat2 * p * 4.);
    f += .03125*noise( fbm2Dmat2 * p * 4.);
    return f;
}

// Adjust the viewport(same as ray tracing proj)
vec2 adjustedViewport()
{
    vec2 xy = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    vec2 viewport = xy * vec2(resolution.x/resolution.y);
    return viewport;
}

// this calculates the water as a height of a given position
float waterH(vec2 p)
{
    float height = 0.;

    //
    vec2 shift1 = vec2(currentTime) * vec2(.2);

    //Big wave shift
    vec2 shift2 = vec2(currentTime) * wavespeed;

    float wave = 0.0;

    //Consider large wave
    wave += sin(p.x*0.02  + shift2.x)*2.;
    wave += sin(p.x*0.02+p.y*0.01 + shift2.x*1.12) * 3.0;
    wave -= sin(p.x*0.01+p.y*0.001 + shift2.x*0.12) * 4.;
    wave += sin(p.x*0.03112+p.y*0.01122+shift2.x*4.269)*2.5;
    wave *= bigwave;

    //Consider small waves
    wave -= fbm2D(p*0.004-shift2*.5)*smallwave*24.;

    //The initial amplitude for a small wave
    //the amplitude decrease by half per octave
    float amp = 6. * smallwave;
    for (int i = 0; i < waterOctaves; i++)
    {
        wave -= abs(sin((noise(p*0.01+shift1)-.5)*3.14))*amp;
        amp *= .5;
        shift1 /= 3.;
        p *= fbm2Dmat2 * 4.;
    }

    height += wave;
    return height;
}

float map(vec3 p)
{
    return p.y - waterH(p.xz);
}

//Soft shadow function for mapping the cloud shadow onto the water surface
//The shift direction, velocity and noise function SHOULD BE SAME
//with the function we used to compute the cloud color
//The shadow is based on how much density the reflection ray is gained
//during the shadowing mapping
//** The uniformed parameter shadowHardness is used for controlling the hardness of the shadow
float shadow(vec3 ro, vec3 rd)
{
    float height = 450.;
    float t = 0.;

    //Final shadow value for the current reflected ray
    float shadow = 0.;
    for(int layer = 0; layer < 10; ++ layer){
        float dist = (t * 1. + height - ro.y) / rd.y;
        vec3 cloudpos = ro + dist * rd;
        vec3 shiftto = vec3(100. , height + layer * .15 - cloudshift.x * 0.01, 500. + cloudshift.y * 4.);
        cloudpos += shiftto;
        float darkness = smoothstep(0.5, 1.0, fbm3D(cloudpos * 0.0012)) * .9;
        shadow += (1. - shadow) * darkness;
        if(shadow > shadowHardness) break;
        t += 100.;
    }

    if(renderCloud && renderShadow) return clamp(1 - shadow, 0., 1.);
    else return 1.;
}

//Core ray march function, this function returns true if the ray
//eventually hits the ocean, otherwise returns false (hits the sky)
bool raymarch(vec3 ro, vec3 rd, out float dist)
{
    float t, h = 0.;

    //The distance that ray marches each iteration.
    //The step is dynamically adjusted for exp. when the ray is look toward sky
    //or the marched point is relatively far away from where itself emits
    float step = 1.;

    //Step factor
    float f = 1.;

    //The current position of the ray
    vec3 pos = ro;

    for(int s = 0; s < march_steps; ++s){

        pos = ro + t * rd;
        h = map(pos);

        //Terminate ray marching if either an intersection is found
        //or it exceeds the far limit
        if(h < .1 || pos.y > march_far){
            dist = t;
            return (h < 10.) ? true : false;
        }

        //Dynamically adjust the ray marching step
        //1.If the ray travels far away
        //2.If we look toward the sky
        //3.If we are looking toward the ocean, the closer the ray and ocean
        //the smaller the marching step is.

        //** Condition 1 **//
        if(t > 600.){
           step = 4.5;
        }

        //** Condition 2 **//
        if(rd.y > 0.){
            f = 35.;
        }

        //** Condition 3 **//
        else{
           f = h;
        }

        t += f * step;
    }

    dist = t;

    return false;
}

//Update the camera position according to the user input.
vec3 camRotate( float time )
{
    vec4 cam = fragMVP * vec4(camX, 0.0, 1000.*time, 1.0);
    return cam.xyz;
}

//Setup the camera before ray marching and render process
Camera setupCam()
{
    Camera cam;

    float time = currentTime*.05;
    vec3 campos = camRotate( time );
    vec3 targetpos = camRotate(time + 3.);

    //Make sure the camera is above the sea level
    campos.y = camY;
    targetpos.y = campos.y * .8;

    //w is the negative look vector
    vec3 w = -normalize(targetpos-campos);

    //** Be careful the PARAMETER SEQUENCE when use the cross:
    //x[1]*y[2]−y[1]*x[2]
    //x[2]*y[0]−y[2]*x[0]
    //x[0]*y[1]−y[1]*x[0]
    //**

    //Defines the up vector, since the camera is rolling, update the up vector coorespondly
    vec3 up = vec3(sin(.1*sin(time*1.2)), cos(.1*sin(time*1.2)),0.0);

    // u is perpendicular the up-w plane
    vec3 u = normalize(cross(w,up));

    // v is perpendicular to both w and u
    vec3 v = normalize(cross(u,w));


    //Set up camera parameters
    cam.pos = campos;
    cam.look = -w;
    cam.w = w;
    cam.v = v;
    cam.u = u;
    cam.trans = mat3(u, v, w);

    return cam;
}

//This fog only takes the distance from the camera to the intersection point into account,
//the further the in the scene, the thicker the fog would be.
//For exp, when dist=0, fogamount = 0 and therefore no fog is applied on this pixel.
vec3 distFog(vec3 col, float dist)
{
    float fogAmount = smoothstep(0.,1.,1.0 - exp(-0.0002 * dist));
    col = mix( col, fogcolor, fogAmount );
    return col;
}

//This is a more realistic fog, it takes extra information into account: the angle between
//the light and the ray direction. The smaller the angle, the brighter the fog would be.
//Make sure the dot product should be no less than 0.
vec3 realFog(vec3 col, float dist, vec3 rd, vec3 ld)
{
    float fogAmount = 1.0 - exp( -0.0001 * dist );
    float sunAmount = max( dot( rd, ld ), 0.0 );
    vec3  fc  = mix( vec3(0.5,0.5,0.5),
                     suncolor,
                     pow(sunAmount,5.0) );
    return mix( col, fc, fogAmount );
}

//Height fog, the more higher in the scene, the sparser the fog is.
vec3 heightFog(vec3 col, float dist, vec3 ro, vec3 rd)
{
    float fogAmount = 0.0005*(ro.y+dist*rd.y) * exp(-ro.y*0.0005) * (1.0-exp( -dist*rd.y*0.0005 ))/rd.y;
    vec3  fc  = vec3(1.,1.,1.);
    return mix( col, fc, fogAmount );
}

vec4 rendercloud(vec3 ro, vec3 rd){

    vec4 cloudcol = vec4(0,0,0,0);

    //Height of the cloud
    float height = 450.;

    //Increase octaves will decrease the rendering speed but with a higher quality
    for (int layer = 0; layer < cloudOctaves; ++layer)
    {
        //Distance from origin of the ray to current cloud layer
        //** P = RO + T * RD  --> T = (P - RO) / RD **//
        float dist = (layer * 1. * cloudThickness + height - ro.y) / rd.y;

        //Real cloud layer position
        vec3 cloudpos = ro + dist * rd;

        //Shift direction of the current layer
        //x --> Left - right shift
        //y --> Up and down shift
        //z --> Near and far shift
        vec3 shiftto = vec3(100., height+ layer *.15 - cloudshift.x * 0.01, 500. + cloudshift.y * 4.0);

        //Apply position shift to the original layer position
        cloudpos += shiftto;

        //Genrate random darkness value for the current cloud layer based on noise and fbm function
        float darkness = smoothstep(0.5, 1.0, fbm3D( cloudpos * 0.0012 ))*.9;

        //Interpolate between the white and darkcloud color
        vec3 layercol = mix(vec3(1.05), darkcloud, darkness);

        //Adjust darkness based on the accumulative cloud darkness
        darkness *= (1.0 - cloudcol.w);

        cloudcol += vec4(layercol * darkness, darkness);

        //If the alpha value is big enough, which means that the contribution from higher layers
        //can be ignored, we exit the render loop (can speed up the cloud render process)
        if (cloudcol.w > 0.99) break;
    }

    float drakness = smoothstep(0.7, 1.0, cloudcol.w);
    cloudcol.rgb /= cloudcol.w;

    float diffuse = clamp(dot(rd,light), 0., 1.);
    cloudcol.rgb -= 0.8 * vec3(0.8, 0.75, 0.7) * pow(diffuse,5.) * drakness;
    cloudcol.rgb += 0.2 * suncolor * pow(diffuse,20.0) * (1.0-drakness);

    return cloudcol;
}

//** Calculate water normal at the given position **//
vec3 getWaterNormal(vec3 pos, float t)
{
    vec2 eps = vec2(.002 * t, .0);
    return normalize(vec3(waterH(pos.xz-eps.xy) - waterH(pos.xz+eps.xy),
                          2.0*eps.x,
                          waterH(pos.xz-eps.yx) - waterH(pos.xz+eps.yx)));
}

//Render the star when night falls
vec3 renderStar(vec3 p, bool day)
{
    vec3 star = vec3(0.);
    float val = starNoise(p);
    if(max(val, sparse) == val){

        //Alpha is based on the movement of the sun
        float alpha = fract(sin(currentTime * .1));

        if(day){
          star += vec3(pow((val - sparse)/(1.0 - sparse), 6.0 )) * clamp(1.-alpha * 4.,0.,0.5);
        }else{
          star += vec3(pow((val - sparse)/(1.0 - sparse), 6.0 )) * clamp(alpha * 5,.9,1.);
        }
    }

    return star;
}

vec3 renderLensEffect(Camera cam, vec2 viewport,vec3 rd)
{
    vec3 lenscol = vec3(0.);
    float pi = 3.1415926;
    float intensity = dot(light, cam.w) * .8;
    vec3 pos = cam.trans * light;
    if(intensity > 0.4){
        intensity = pow(intensity, 8.) * .8;
        float glare = max(dot(normalize(vec3(rd.x, rd.y+.3, rd.z)),light),0.0)*1.4;
        float glare3 = max(1.0-length(pos.xy - viewport * 2.1), 0.0);
        float glare4 = max(sin(smoothstep(-0.05, .4, length(pos.xy + viewport*2.5))*pi), 0.0);

        lenscol += intensity * vec3(1.0, .0, .0)  * pow(glare, 12.5)*.07;
        lenscol += intensity * suncolor * pow(glare3, 3.0)*4.0;
        lenscol += intensity * vec3(.5, 1.0, 1.0) * pow(glare4, 33.9)*.7;
    }

   return lenscol;
}

vec3 renderSky(vec3 ro, vec3 rd, float coefd, vec3 p)
{
    //Final sky color
    vec3 sky = vec3(0.);

    //How big is the sun
    float blend = pow(1. -.5*rd.y, 20.);

    //Color for cloud
    vec4 cloudcolor = vec4(0.);

    //Make sure that the cloud will block the stars
    bool day = sunshift > .0;
    if(day){
        sky = mix(suncolor,mix(skycolor * 2., nightskycolor, smoothstep(.0,1., 1.-fract(light.y))), 1-blend);
    }else{
        sky = mix(suncolor,mix(skycolor * .5, nightskycolor, smoothstep(.0,1.,fract(light.y))), 1-blend);
    }

    sky *= .7;

    sky += suncolor * pow( coefd, 500.0 );

    sky += sunhazecolor * pow( coefd, 10.0 );

    if(renderCloud){
        cloudcolor = rendercloud(ro, rd);
        sky = mix(sky, cloudcolor.xyz, cloudcolor.w * (1. - blend));
    }

    //Make sure that the cloud will block stars
    //check x not equals to 0 is enough since cloud
    //originally has a default color.
    if(cloudcolor.x != 0){
        sky += renderStar(p, day);
    }

    return sky;
}

vec3 renderWater(vec3 pos, float dist, vec3 rd)
{
    vec3 normal = getWaterNormal(pos, dist);

    //Final water color
    vec3 water = vec3(0.);

    //Reflection of the ray after hitting the ocean surface
    rd = reflect (rd, normal);

    //How much does the sky contributes to the water color
    //The normal of the sky plane is (0, 1, 0)
    float skyreflection = 1.0-clamp(dot(rd,vec3(0.0, 1.0, 0.0)),0.0,1.0);

    //Shadow created by moving cloud
    float shadow = shadow(pos, rd);


    float diffuse = clamp(dot(rd,light),0.,1.);

    //Mix the water with the sky color then apply shadow
    water = mix(reflskycolor, watercolor, skyreflection) * shadow;
    water += vec3(.003, .005, .005) * (pos.y+30.);

    // Sun
    float wsunrefl = skyreflection * shadow * (0.5*pow( diffuse, 10.0 )+0.25*pow( diffuse, 3.5)+.75*pow( diffuse, 300.0));
    water += vec3(1.5,1.3,1.0) * wsunrefl; // sun reflection

    return water;
}

vec3 renderWeather(Camera cam, vec3 rd, float dist,vec3 light)
{ 
    vec3 raincol = vec3(0.);
    vec3 p = cam.pos + dist * rd;
    vec2 viewport =  gl_FragCoord.xy / resolution.xy;
    vec3 newViewport = cam.trans * vec3(viewport, 0.);

    //Inital t for rain marching ray
    float t = 1.;

    if(renderRain || renderSnow){

        //rainOctaves represents how many layers are taken into account when reder rain drop
        for(int i = 0;i < rainOctaves; ++i){
            vec3 curpos = cam.pos + t * rd;

            if(curpos.z < p.z){

                float chain,thickness = .0;

                if(renderRain){
                    thickness = .1;
                    chain = 31.5;
                }else{
                    thickness = .9;
                    chain = 23.5;
                }
                float seq = pow(t, 1.1);

                //The direction of rain fall x-->Left or right / y-->back or toward
                vec2 st = seq * (newViewport.xy * vec2(resolution.x / resolution.y , thickness) + vec2(-currentTime * .1 + newViewport.y * .3, currentTime * .5));
                seq = abs((texture(noise_texture, st * .5, -100.).x + texture(noise_texture, st * .284, 100.).y));
                seq = clamp(pow(seq * .5, chain) * 140. , 0., .5);
                //Basic brightness of the rain drop
                vec3 brightness = vec3(.25);
                float dot = clamp(dot(rd,light),.4,1.) * .2;
                brightness += dot;
                raincol += brightness * seq;
            }

            //March distance for the current ray
            t += 3.;
        }

        raincol = clamp(raincol, 0., 1.);
    }

    return raincol;
}

void main()
{

    vec2 viewport = adjustedViewport();

    //Setup the camera for the current frame
    Camera cam = setupCam();

    //** Important to do **//
    //Before start ray marching, we have to transform the ray direction from
    //the u,v,z coord to the camera coord
    //the bigger z is, the less we can see through the screen
    vec3 rd = normalize(cam.trans * vec3(viewport, wideAngle));

    float diffuse = clamp(dot(rd,light),-.1, 1.);

    //Final color
    vec3 col = vec3(0.);
    float dist = 0.;

    //The march function returns true if the ray eventually hits the water surface --> then we have to render water,
    //convertly, march returns false if the ray lost in the sky --> then we have to render sky.
    if(!raymarch(cam.pos, rd, dist))
    {
        //Let the mvp matrix transform the original viewport into a new viewport when we
        //rotate the camera and use the new viewport to generate star noise so that
        //the stars can look more realistic.
        //If we use the original viewport, stars won't change as we move the camera around
        vec4 newViewport = fragMVP * vec4((viewport + 1.) / 2., 0., 0.);
        col = renderSky(cam.pos, rd, diffuse, newViewport.xyz);
    }
    else
    {
        vec3 wpos = cam.pos + dist * rd;
        col = renderWater(wpos, dist, rd);
    }

    vec3 rainColor = renderWeather(cam,rd,dist,light);
    col += rainColor;

    if(renderLens){
        col += renderLensEffect(cam, viewport, rd);
    }

    //**APPLY FOG AT LAST IF FOD EFFECT IS ENABLED**//
    //First line -> global constant fog

    if(renderFog){
        col = realFog(col, dist, rd, light);
    }

    fragColor= col;
}
