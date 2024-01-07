#version 460 core

out vec4 outColor;
in vec4 vertColor;

uniform float setColor;

void main() {
    outColor = vec4(setColor, setColor, setColor, 1);
}