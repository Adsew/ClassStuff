#version 120

attribute vec3 vertexPosition_modelspace;

uniform in vec4 colour;
varying out vec4 fragColour;

void main() {

    //mat3x4 m1 = mat3x4(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12); // 3x4

    //mat3x2 m2 = mat3x2(1, 2, 3, 4, 5, 6); // 3x2

    //mat2x3 m3 = mat2x3(1, 2, 3, 4, 5, 6); // 2x3

    //mat4x3 m4 = mat4x3(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12); // 4x3

    //mat4x2 m5 = mat4x2(1, 2, 3, 4, 5, 6, 7, 8); // 4x2


    //mat2x4 m6 = m1 * m3;

    //mat4x4 m7 = m1 * m4;

    //mat3x3 m8 = m4 * m1;

    //mat4x2 m9 = m5 * m7;

    //mat4x4 v1 = m1 * vec4();

    //vec2 v2 = m2 * vec2();

    //vec2 v3 = m6 * vec2();

    //vec4 v4 = vec4() * m1;

    //vec2 v5 = vec2() * m2;

    //vec2 v6 = vec2() * m6;

    gl_Position = vec4(vertexPosition_modelspace, 1.0);
    fragColour = colour;
}
