﻿#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textCoord;

out vec4 vertColor;
out vec2 vertTextCoord;

uniform float time;

void main() {
    gl_Position = vec4(pos, 1);
    vertColor = vec4(color, 1f);
    vertTextCoord = textCoord;
}
