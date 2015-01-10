#version 330 core

varying vec3 pos;

out vec3 color;

void main() {
    color = pos*10;
}
