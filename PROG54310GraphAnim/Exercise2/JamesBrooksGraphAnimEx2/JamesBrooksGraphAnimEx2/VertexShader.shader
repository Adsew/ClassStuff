#version 120

attribute vec3 vertexPosition_modelspace;

uniform in vec4 colour;
varying out vec4 fragColour;

void main() {

    gl_Position = vec4(vertexPosition_modelspace, 1.0);
    fragColour = colour;
}
