#version 460 core

out vec4 outColor;
in vec4 vertColor;

uniform float setAlpha;

void main() {
    outColor = vec4(setAlpha, setAlpha, setAlpha, 1);
}