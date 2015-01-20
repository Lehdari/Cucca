#version 330 core

varying vec2 texCoord_;
varying vec3 normal_;
varying vec3 normal_clip_;

out vec3 color;

uniform sampler2D sampler;

void main() {
    float f = gl_FragCoord.z / (gl_FragCoord.w * 25.0);
    color = texture(sampler, texCoord_).rbg * (dot(normal_clip_, vec3(0.0, 0.0, 1.0)) - f);
}
