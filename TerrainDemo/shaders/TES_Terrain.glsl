/**
    Cucca Game Engine - TerrainDemo - TES_Terrain.glsl

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#version 400 core


layout(triangles, equal_spacing, ccw) in;


in vec4 in_TES_position[];
in vec3 in_TES_texCoord[];
in vec3 in_TES_normal[];

out vec4 in_FS_position;
out vec3 in_FS_texCoord;
out vec3 in_FS_normal;

uniform mat4 camera;
uniform sampler2D displacementMap;
const float displacementFactor = 8.0;


vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2) {
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}


void main() {
   	// Interpolate the attributes of the output vertex using the barycentric coordinates
   	in_FS_position = vec4(interpolate3D(in_TES_position[0].xyz, in_TES_position[1].xyz, in_TES_position[2].xyz), 1.0);
   	in_FS_texCoord = interpolate3D(in_TES_texCoord[0], in_TES_texCoord[1], in_TES_texCoord[2]);
   	in_FS_normal = interpolate3D(in_TES_normal[0], in_TES_normal[1], in_TES_normal[2]);
   	in_FS_normal = normalize(in_FS_normal);

   	// Displace the vertex along the normal
   	float disp = texture(displacementMap, in_FS_texCoord.xy*64).x;
   	in_FS_position += vec4(in_FS_normal * disp * displacementFactor, 0.0);
   	gl_Position = camera * in_FS_position;
}
