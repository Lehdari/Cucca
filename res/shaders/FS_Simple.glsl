#version 330 core

varying vec4 pos;

out vec3 color;

void main() {
    color = pos.xyz;
}
