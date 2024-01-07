#version 460 core
out vec4 outColor;
in vec4 vertColor;

uniform vec4 setColor;

void main() {
    outColor = vertColor;
    
}