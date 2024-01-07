#version 460 core
in vec4 vertColor;
in vec2 vertTextCoord;

out vec4 resultColor;

uniform sampler2D obamnaTexture;

void main() {
    resultColor = texture(obamnaTexture, vertTextCoord) * vertColor;
}
