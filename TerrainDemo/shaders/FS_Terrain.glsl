/**
    Cucca Game Engine - TerrainDemo - FS_Terrain.glsl

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#version 400 core


in vec4 in_FS_position;
in vec3 in_FS_texCoord;
in vec3 in_FS_normal;

out vec4 out_color;

uniform sampler2D diffuse;


void main() {
    out_color = texture(diffuse, in_FS_texCoord.xy);
}
