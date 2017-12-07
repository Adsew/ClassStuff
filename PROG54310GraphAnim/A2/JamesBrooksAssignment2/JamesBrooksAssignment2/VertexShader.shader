#version 330

in vec3 vec3_position;

uniform mat4 mvp_camera;

in vec4 vec4_light_colour;
out vec4 lighting_colour;

in vec4 vec4_colour;
out vec4 frag_colour;

void main() {

    gl_Position = mvp_camera * vec4(vec3_position, 1.0);
    
    frag_colour = vec4_colour;
    lighting_colour = vec4_light_colour;
}
