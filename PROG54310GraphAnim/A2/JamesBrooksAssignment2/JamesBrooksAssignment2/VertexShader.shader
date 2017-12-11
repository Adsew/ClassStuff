#version 330


// Camera

uniform mat4 mvp_camera;


// Object

in vec3 vec3_position;

in vec4 vec4_colour;
out vec4 frag_colour;


void main() {

    gl_Position = mvp_camera * vec4(vec3_position, 1.0);
    

    // Transfers to fragment shader

    frag_colour = vec4_colour;
}
