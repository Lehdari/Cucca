/**
    Cucca Game Engine - TerrainDemo - TES_Terrain.glsl

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#version 400 core


layout(quads) in;


in vec4 in_TES_position[];
in vec3 in_TES_texCoord[];
in vec3 in_TES_normal[];

out vec4 in_FS_position;
out vec3 in_FS_texCoord;
out vec3 in_FS_normal;
out vec3 in_FS_color;   //  TEMP

uniform mat4 camera;
uniform sampler2D displacementMap;
const float displacementFactor = 0.0;


const mat4 ip = mat4(   2.0,    -2.0,   1.0,    1.0,
                        -3.0,   3.0,    -2.0,   -1.0,
                        0.0,    0.0,    1.0,    0.0,
                        1.0,    0.0,    0.0,    0.0 );

vec3 interpolateSpline(vec3 p1, vec3 p2, vec3 t1, vec3 t2, float t) {
    vec4 s = vec4(t*t*t, t*t, t, 1.0);

    vec4 vx = vec4(p1.x, p2.x, t1.x, t2.x);
    vec4 vy = vec4(p1.y, p2.y, t1.y, t2.y);
    vec4 vz = vec4(p1.z, p2.z, t1.z, t2.z);

    return vec3(dot(vx*ip, s), dot(vy*ip, s), dot(vz*ip, s));
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2) {
   	return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

vec3 interpolateQuad(vec3 v0, vec3 v1, vec3 v2, vec3 v3) {
    vec3 t1 = v0 + gl_TessCoord.x*(v1-v0);
    vec3 t2 = v2 + gl_TessCoord.x*(v3-v2);

   	return t1 + gl_TessCoord.y*(t2-t1);
}

vec3 interpolateQuad2(vec4 pos[4], vec3 normal[4]) {
    vec3 t1 = interpolateSpline(pos[0].xyz, pos[1].xyz, normal[0], normal[1], gl_TessCoord.x);
    vec3 t2 = interpolateSpline(pos[2].xyz, pos[3].xyz, normal[2], normal[3], gl_TessCoord.x);

    //  TODO: fix y-normals
   	return interpolateSpline(t1, t2, vec3(0.0, 1.0, 0.0), vec3(0.0, 1.0, 0.0), gl_TessCoord.y);
}


void main() {
    vec4 pos[4] = vec4[4](in_TES_position[0], in_TES_position[1], in_TES_position[2], in_TES_position[3]);
    vec3 nor[4] = vec3[4](in_TES_normal[0], in_TES_normal[1], in_TES_normal[2], in_TES_normal[3]);
    in_FS_position = vec4(interpolateQuad2( pos, nor), 1.0);
   	in_FS_texCoord = interpolateQuad(in_TES_texCoord[0], in_TES_texCoord[1], in_TES_texCoord[2], in_TES_texCoord[3]);
   	in_FS_normal = interpolateQuad(in_TES_normal[0], in_TES_normal[1], in_TES_normal[2], in_TES_normal[3]);
   	in_FS_normal = normalize(in_FS_normal);
   	in_FS_color = vec3(gl_TessCoord.x, gl_TessCoord.y, 0.0);//0.5+0.5*in_FS_normal;

   	// Displace the vertex along the normal
   	float disp = texture(displacementMap, in_FS_texCoord.xy*64).x-0.5;
   	in_FS_position += vec4(in_FS_normal * disp * displacementFactor, 0.0);
   	gl_Position = camera * in_FS_position;
}
