#version 120

attribute vec3 vertexPosition_modelspace;

uniform mat4 MVP_camera;
uniform in vec4 colour;
varying out vec4 fragColour;

void main() {

    gl_Position = MVP_camera * vec4(vertexPosition_modelspace, 1.0);
    fragColour = colour;
}
