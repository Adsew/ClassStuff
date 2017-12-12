#version 330


// Camera

uniform mat4 mvp_camera;


// Object

in vec3 vec3_position;
out vec3 frag_position;

in vec3 vec3_normal;
out vec3 vert_normal;

in vec4 vec4_colour;
out vec4 frag_colour;


void main() {

    gl_Position = mvp_camera * vec4(vec3_position, 1.0);
    

    // Transfers to fragment shader

    frag_position = vec3_position;
    vert_normal = vec3_normal;
    frag_colour = vec4_colour;
}
