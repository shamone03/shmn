#version 460 core
in vec4 vertColor;
in vec2 vertTextCoord;

out vec4 resultColor;

uniform sampler2D saul_jpg;
uniform sampler2D hamster_png;

void main() {
    resultColor = mix(texture(saul_jpg, vertTextCoord), texture(hamster_png, vertTextCoord), 0.6) * vertColor;
}
