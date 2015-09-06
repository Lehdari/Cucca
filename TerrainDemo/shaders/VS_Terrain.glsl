/**
    Cucca Game Engine - TerrainDemo - VS_Terrain.glsl

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#version 420 core


layout(location = 0) in vec4 in_VS_position;
layout(location = 1) in vec3 in_VS_texCoord;
layout(location = 2) in vec3 in_VS_normal;

layout(location = 0) out vec4 in_TCS_position;
layout(location = 1) out vec3 in_TCS_texCoord;
layout(location = 2) out vec3 in_TCS_normal;

uniform mat4 model;


void main() {
    in_TCS_position = model * in_VS_position;
    in_TCS_texCoord = in_VS_texCoord;
    in_TCS_normal = normalize((model * vec4(in_VS_normal, 0.0)).xyz);
    gl_Position = in_TCS_position;
}
