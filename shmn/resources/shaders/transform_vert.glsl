#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textCoord;

out vec4 vertColor;
out vec2 vertTextCoord;

uniform mat4 transform;

void main() {
    gl_Position = transform * vec4(pos, 1.0f);
    vertColor = vec4(color, 1f);
    vertTextCoord = textCoord;
}
