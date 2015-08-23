/**
    Cucca Game Engine - TerrainDemo - TES_Terrain.glsl

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#version 400 core


//layout(triangles, equal_spacing, ccw) in;
layout(quads) in;


in vec4 in_TES_position[];
in vec3 in_TES_texCoord[];
in vec3 in_TES_normal[];

out vec4 in_FS_position;
out vec3 in_FS_texCoord;
out vec3 in_FS_normal;

uniform mat4 camera;
uniform sampler2D displacementMap;
const float displacementFactor = 0.0;


vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2) {
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

vec3 interpolateQuad(vec3 v0, vec3 v1, vec3 v2, vec3 v3) {
    vec3 t1 = v0 + gl_TessCoord.x*(v1-v0);
    vec3 t2 = v2 + gl_TessCoord.x*(v3-v2);

   	return t1 + gl_TessCoord.y*(t2-t1);
}


void main() {
   	// Interpolate the attributes of the output vertex using the barycentric coordinates
   	/*in_FS_position = vec4(interpolate3D(in_TES_position[0].xyz, in_TES_position[1].xyz, in_TES_position[2].xyz), 1.0);
   	in_FS_texCoord = interpolate3D(in_TES_texCoord[0], in_TES_texCoord[1], in_TES_texCoord[2]);
   	in_FS_normal = interpolate3D(in_TES_normal[0], in_TES_normal[1], in_TES_normal[2]);
   	in_FS_normal = normalize(in_FS_normal);*/

    in_FS_position = vec4(interpolateQuad(in_TES_position[0].xyz, in_TES_position[1].xyz, in_TES_position[2].xyz, in_TES_position[3].xyz), 1.0);
   	in_FS_texCoord = interpolateQuad(in_TES_texCoord[0], in_TES_texCoord[1], in_TES_texCoord[2], in_TES_texCoord[3]);
   	in_FS_normal = interpolateQuad(in_TES_normal[0], in_TES_normal[1], in_TES_normal[2], in_TES_normal[3]);
   	in_FS_normal = normalize(in_FS_normal);

   	// Displace the vertex along the normal
   	float disp = texture(displacementMap, in_FS_texCoord.xy*64).x-0.5;
   	in_FS_position += vec4(in_FS_normal * disp * displacementFactor, 0.0);
   	gl_Position = camera * in_FS_position;
}
