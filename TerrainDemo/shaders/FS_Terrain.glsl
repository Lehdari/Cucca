/**
    Cucca Game Engine - TerrainDemo - FS_Terrain.glsl

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#version 420 core


in vec4 in_FS_position;
in vec3 in_FS_texCoord;
in vec3 in_FS_normal;
in vec3 in_FS_color;    //  TEMP

out vec4 out_color;

uniform sampler2D diffuse;


void main() {
    out_color = texture(diffuse, in_FS_texCoord.xy);
    //out_color = vec4(in_FS_color, 1.0);
}
