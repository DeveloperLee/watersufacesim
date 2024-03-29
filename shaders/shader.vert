#version 400 core

layout(location = 0) in vec3 position;

uniform mat4 model, view, projection;

void main() {

    gl_Position = projection * view * model *  vec4(position, 1.0);
//    gl_Position = vec4(position, 1.0);
}
