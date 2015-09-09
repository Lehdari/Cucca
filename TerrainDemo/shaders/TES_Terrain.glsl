/**
    Cucca Game Engine - TerrainDemo - TES_Terrain.glsl

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#version 420 core


layout(quads, equal_spacing, ccw) in;


in vec3 in_TES_CP_position[];
patch in vec3 in_TES_texCoord[4];
patch in vec3 in_TES_normal[4];

out vec4 in_FS_position;
out vec3 in_FS_texCoord;
out vec3 in_FS_normal;
out vec3 in_FS_color;   //  TEMP

uniform mat4 camera;
uniform sampler2D displacementMap;
const float displacementFactor = 0.0;


vec3 interpolateQuad(vec3 v0, vec3 v1, vec3 v2, vec3 v3) {
    vec3 t1 = v0 + gl_TessCoord.x*(v1-v0);
    vec3 t2 = v2 + gl_TessCoord.x*(v3-v2);

   	return t1 + gl_TessCoord.y*(t2-t1);
}

float bernstein(int i, float x) {
    int a = i*(3-i)+1;

    return a*pow(x, i)*pow(1.0-x,3-i);
}

vec3 bezierSurface(vec3 cp[16]) {
    vec3 p = vec3(0.0);
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            p += bernstein(i, gl_TessCoord.x) * bernstein(j, gl_TessCoord.y) * cp[i+4*j];
        }
    }
    return p;
}


void main() {
    vec3 p = vec3(0.0);
    for (int i=0; i<4; ++i) {
        for (int j=0; j<4; ++j) {
            p += bernstein(i, gl_TessCoord.x) * bernstein(j, gl_TessCoord.y) * in_TES_CP_position[i+4*j];
        }
    }
    in_FS_position = vec4(p, 1.0);

   	in_FS_texCoord = interpolateQuad(in_TES_texCoord[0], in_TES_texCoord[1], in_TES_texCoord[2], in_TES_texCoord[3]);
   	in_FS_normal = interpolateQuad(in_TES_normal[0], in_TES_normal[1], in_TES_normal[2], in_TES_normal[3]);
   	in_FS_normal = normalize(in_FS_normal);
   	in_FS_color = in_FS_normal*0.5 + 0.5;//vec3(gl_TessCoord.x, gl_TessCoord.y, 0.0);

   	// Displace the vertex along the normal
   	float disp = texture(displacementMap, in_FS_texCoord.xy*64).x-0.5;
   	in_FS_position += vec4(in_FS_normal * disp * displacementFactor, 0.0);
   	gl_Position = camera * in_FS_position;
}
