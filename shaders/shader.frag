#version 400 core

#define INTERSECTION_THRESHOLD 0.1
#define RENDER_CLOUDS 1
#define OCTAVES 7
#define TRACE_STEPS 120

uniform ivec2 resolution;           // Screen resolution
uniform mat4 fragMVP;                // MVP matrix for handling camera rotation
uniform mat3 motionMatrix1;
uniform float currentTime;           // Current time in seconds
uniform float cloudThickness;  // Thinkness of the cloud
uniform bool renderFog;                 // True: apply fog, False: doesn't apply fog
uniform bool renderCloud;
uniform sampler2D sampler;           // Texture sampler

float waterlevel = 30.0;        // height of the water
float large_waterH = 1.0; // change to adjust the "heavy" waves (set to 0.0 to have a very still ocean :)
float small_waterH = .5; // change to adjust the small waves
float diff = 0.;
float sparse = 0.99;

vec3 fogcolor    = vec3( 0.5, 0.5, 0.5);
vec3 suncolor   = vec3( 1.0, 0.9, 0.7 );
vec3 sunhazecolor = vec3(.77,.57,.432);
vec3 nightSuncolor = vec3(151., 153., 155.) / 255.;

vec3 skycolor       = vec3(.53, .807, .9215);
vec3 nightskycolor  = vec3(0.1, 0.2, 0.4);
vec3 reflskycolor = vec3(0.025, 0.10, 0.20);
vec3 watercolor   = vec3(0.2, 0.25, 0.3);

float sunshift = sin(currentTime * .1);

vec3 light = normalize( vec3(0.3, clamp(sunshift,-1.,.3),  0.8) );

mat2 fbm2Dmat2 = mat2(.4,-.3,.4,.3);

struct Camera{

    vec3 pos; //Current position of the camera
    vec3 look; //Look vector
    vec3 u,v,w; //u,v,w coordinate of the camera
};

out vec3 fragColor;      // Final output color for each pixel

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
  return texture(sampler,p / 256.).x;
}

// 3d noise function
float noise(vec3 v)
{
    vec3 p = floor(v);
    vec3 f = fract(v);
    f = f*f*(3.-2.*f);

    vec2 uv = (p.xy+vec2(37.,17.)*p.z) + f.xy;
    vec2 rg = texture( sampler, (uv+.5)/256., -100.).yx;
   return mix(rg.x, rg.y, f.z);
}

float starNoise(vec3 p)
{
    float xhash = hash2( p.x * 37.0 );
    float yhash = hash2( p.y * 57.0 );
    float zhash = hash2( p.z * 77.0 );
    return fract( xhash + yhash + zhash );
}

mat3 m = mat3( 0.00,  1.60,  1.20, -1.60,  0.72, -0.96, -1.20, -0.96,  1.28 );

// Fractional Brownian motion
float fbm3D( vec3 p )
{
  float f = .5*noise( p );
  f += .25*noise( m * p);
  f += .125*noise( m * p);
  f += .0625*noise( m * p );
  return f;
}

// Fractional Brownian motion
float fbm2D( vec2 p )
{
  float f = .5*noise( p);
  f += .25*noise( fbm2Dmat2 * p * 4.);
  f += .125*noise( fbm2Dmat2 * p * 4.);
  f += .0625*noise( fbm2Dmat2 * p * 4.);
  return f;
}

// Adjust the viewport(same as ray tracing proj)
vec2 adjustedViewport()
{
    vec2 xy = -1.0 + 2.0 * gl_FragCoord.xy / resolution.xy;
    vec2 viewport = xy*vec2(resolution.x/resolution.y * 1.5,1.0);
    return viewport;
}

// this calculates the water as a height of a given position
float waterH(vec2 p)
{
  float height = waterlevel;

  vec2 shift1 = vec2(currentTime) * vec2(.08);
  vec2 shift2 = vec2(currentTime) * vec2(.17,-.10);

  float wave = 0.0;
  wave += sin(p.x*0.021  + shift2.x)*4.5;
  wave += sin(p.x*0.0172+p.y*0.010 + shift2.x*1.121)*4.0;
  wave -= sin(p.x*0.00104+p.y*0.005 + shift2.x*0.121)*4.0;
  wave += sin(p.x*0.02221+p.y*0.01233+shift2.x*3.437)*5.0;
  wave += sin(p.x*0.03112+p.y*0.01122+shift2.x*4.269)*2.5 ;
  wave *= large_waterH;
  wave -= fbm2D(p*0.004-shift2*.5)*small_waterH*24.;

  float amp = 6.*small_waterH;
  shift1 *= .3;
  for (int i = 0; i < OCTAVES; i++)
  {
    wave -= abs(sin((noise(p*0.01+shift1)-.5)*3.14))*amp;
    amp *= .51;
    shift1 *= 1.841;
    p *= fbm2Dmat2 * 3.7;
  }

  height += wave;
  return height;
}

//float terrainH(vec2 x)
//{
//    vec2  p = x;
//        float a = 0.0;
//        float b = 1.0;
//            vec2  d = vec2(0.0);
//        for( int i=0; i<8; i++ )
//        {
//            vec3 n = noised(p);
//            d += n.yz;
//            a += b*n.x/(1.0+dot(d,d));
//                    b *= 0.5;
//            p = fbm2Dmat2 *p*2.0;
//        }

//   return .3*a+.5;
//}

float map(vec3 p)
{
//    float diff1 = p.y - terrainH(p.xz);
//    float diff2 = p.y - waterH(p.xz);
//    diff = diff2 - diff1;
//    return min(diff1,diff2);
    return p.y - waterH(p.xz);
}

float trace_cloud(vec3 ro, vec3 rd )
{
  if(renderCloud){

      vec2 shift = vec2( currentTime*80.0, currentTime*60.0 );
      float sum = 0.0;
      for (int q=0; q<30; q++)
      {
        float c = (1000.-ro.y) / rd.y;// cloud distance
        vec3 cpos = ro + c*rd + vec3(shift.x*3.,0.,shift.y*3.0); // cloud position
        float alpha = smoothstep(0.8, 1.0, fbm3D( (cpos*0.0015) )); // cloud density
        sum += (1.0-sum)*alpha; // alpha saturation
        if (sum>0.98)
            break;
      }
      return clamp( 1.0-sum, 0.0, 1.0 );
  }else{
    return 1.0;
  }
}

bool march(vec3 rStart, vec3 rDirection, float sundot, out float fog, out float dist)
{
  float h = 20.0;
  float t = 0.0;
  float st = 1.0;
  float alpha = 0.1;
  float asum = 0.0;
  vec3 p = rStart;

  for( int s = 0; s < TRACE_STEPS; ++s )
  {

    if( t>500.0 ){
        st = 4.;
    }

    p = rStart + t*rDirection; // calc current ray position

    h = map(p);

    if( h < INTERSECTION_THRESHOLD)
    {
      dist = t;
      fog = asum;
      return true;
    }

    if( p.y>450.0 )
      break;

    // speed up ray if possible...
    if(rDirection.y > 0.0){
      t += 30.0 * st;
    }else{
      t += max(1.0,1.0*h)*st;
    }
  }

  dist = t;
  fog = asum;

  if (h<10.0){
      return true;
  }

  return false;
}

//Update the camera position according to the user input.
vec3 camRotate( float time )
{
  vec4 cam =  fragMVP * vec4(1500.0, 0.0, 1200.0*time, 1.0);
  return cam.xyz;
}

//Setup the camera before ray marching and render process
Camera setupCam()
{
  Camera cam;

  float time = (currentTime)*.05;
  vec3 campos = camRotate( time );
  vec3 targetpos = camRotate( time + 3. );

  //Make sure the camera is above the sea level
  campos.y = waterlevel + 200.;
  targetpos.y = campos.y * .8;

  //w is the negative look vector
  vec3 w = normalize(targetpos-campos);

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

  return cam;
}

//This fog only takes the distance from the camera to the intersection point into account,
//the further the in the scene, the thicker the fog would be.
//For exp, when dist=0, fogamount = 0 and therefore no fog is applied on this pixel.
vec3 distFog(vec3 col, float dist)
{
    float fogAmount = 1.0-exp(-0.0005 * dist);
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

vec4 cloud(vec3 camerapos, vec3 raydirection){

    vec2 shift = vec2(currentTime) * vec2(10., 8.);
    vec4 sum = vec4(0,0,0,0);
    for (int q=0; q<50; q++)
    {
      float c = (float(q)*cloudThickness+500.-camerapos.y) / raydirection.y; // cloud height
      vec3 cpos = camerapos + c*raydirection + vec3(831.0, 321.0+float(q)*.15-shift.x*0.2, 1330.0+shift.y*3.0); // cloud position
      float alpha = smoothstep(0.5, 1.0, fbm3D( cpos*0.0015 ))*.9; // fractal cloud density
      vec3 localcolor = mix(vec3( 1.1, 1.05, 1.0 ), 0.7*vec3( 0.4,0.4,0.3 ), alpha); // density color white->gray
      alpha = (1.0-sum.w)*alpha; // alpha/density saturation (the more a cloud layer's density, the more the higher layers will be hidden)
      sum += vec4(localcolor*alpha, alpha); // sum up weightened color

      if (sum.w>0.44)
        break;
    }

    float alpha = smoothstep(0.7, 1.0, sum.w);

    sum.rgb /= sum.w;
    return sum;
}

//** Calculate water normal at the given position **//
vec3 getWaterNormal(vec3 pos, float t)
{
   vec2 eps = vec2(.002 * t, .0);
   return normalize(vec3(waterH(pos.xz-eps.xy) - waterH(pos.xz+eps.xy),
                         2.0*eps.x,
                         waterH(pos.xz-eps.yx) - waterH(pos.xz+eps.yx)));
}

//** Calculate terrain normal at the given position **//
//vec3 getTerrianNormal(vec3 pos, float t){
//    vec2 eps = vec2(.002 * t, .0);
//    return normalize(vec3(terrainH(pos.xz-eps.xy) - terrainH(pos.xz+eps.xy),
//                          2.0*eps.x,
//                          terrainH(pos.xz-eps.yx) - terrainH(pos.xz+eps.yx)));
//}

//Render the st
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
        cloudcolor = cloud(ro, rd);
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

    vec3 water = vec3(0.);

    rd = reflect (rd, normal);
    float refl = 1.0-clamp(dot(rd,vec3(0.0, 1.0, 0.0)),0.0,1.0);
    float shadow = smoothstep(0.2, 1.0, trace_cloud(pos+20.0*rd,rd))*.7+.3;
    float wsky   = refl * shadow;
    float wwater = (1.0-refl) * shadow;
    float diffuse = clamp(dot(rd,light),-.2,1.);

    water = wsky*reflskycolor;
    water += wwater*watercolor;
    water += vec3(.003, .005, .005) * (pos.y-waterlevel+30.);
    // Sun
    float wsunrefl = wsky*(0.5*pow( diffuse, 10.0 )+0.25*pow( diffuse, 3.5)+.75*pow( diffuse, 300.0));
    water += vec3(1.5,1.3,1.0)*wsunrefl; // sun reflection

    return water;
}

void main()
{

  vec2 viewport = adjustedViewport();

  //Setup the camera for the current frame
  Camera cam = setupCam();
  vec3 rd = normalize( viewport.x*cam.u + viewport.y*cam.v + 1.6*cam.w );

  float diffuse = clamp(dot(rd,light),-.1, 1.);

  //Final color
  vec3 col = vec3(0.);
  float fog=0.0, dist=0.0;


  //The march function returns true if the ray eventually hits the water surface --> then we have to render water,
  //convertly, march returns false if the ray lost in the sky --> then we have to render sky.
  if (!march(cam.pos,rd,diffuse, fog, dist))
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
    vec3 wpos = cam.pos + dist*rd;

    //****BUG HERE****//
    //Can not generate the terrain for now.
    //The idea is that we generate both water and terrain here, if the ray hits the ground surface
    //we know whether it hits on the water surface or terrain surface and render the pixel accordingly.
    if(diff<2.){
       col = renderWater(wpos, dist, rd);
    }else{

//        vec3 normal = getTerrianNormal(wpos, dist);
//        // base rock formation colors
//        vec3 lCol = vec3(1.0, 0.9, 0.7); // yellowish light
//        vec3 color = mix( vec3(0.4, 0.1, 0.0), vec3(0.7, 0.6, 0.3), step(0.9, normal.y) );

//       // layer noise (to produdce lighter color bands of rock)
//       float n = 0.5;
//       // rock layers should show through where nomals are NOT straight up
//       color = mix( vec3(0.6, 0.5, 0.4), color, n*smoothstep(0.0, 0.7, normal.y) );

//      // add in lighting and shadows
//      float lAmb = clamp( 0.5 + 0.5 * normal.y, 0.0, 1.0); // ambient
//      float lDif = clamp( dot( normal, light ), 0.0, 2.0); // diffuse


//      color += (0.4*lAmb) * lCol;
//      color *= (1.8*lDif) * lCol;
//      col = color;
    }
}

  //**APPLY FOG AT LAST IF FOD EFFECT IS ENABLED**//
  //First line -> global constant fog
  //Second line -> lighting fog
  //Third line -> Height-based fog (***BUG***)
  if(renderFog){
//      col = distFog(col, dist);
      col = realFog(col, dist, rd, light);
//      col = heightFog(col, dist, campos, rd);
  }

  fragColor= col;
}