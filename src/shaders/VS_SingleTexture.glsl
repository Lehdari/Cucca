#version 330 core

layout(location = 0) in vec4 _position;
layout(location = 1) in vec3 _texCoord;
layout(location = 2) in vec3 _normal;

out vec2 texCoord_;
out vec3 normal_;
out vec3 normal_clip_;

//uniform mat4 MVP;
uniform mat4 model;
uniform mat4 camera;

void main() {
    gl_Position = camera * model * _position;
    texCoord_ = _texCoord.xy;
    normal_ = normalize(_normal);
    normal_clip_ = normalize((camera * model * vec4(normal_, 1.0)).xyz);
}
