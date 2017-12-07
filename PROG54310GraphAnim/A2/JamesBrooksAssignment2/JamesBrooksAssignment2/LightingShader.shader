#version 330

in vec4 lighting_colour;

in vec4 frag_colour;

out vec4 FragColour;

void main() {

    FragColour = frag_colour;
}
