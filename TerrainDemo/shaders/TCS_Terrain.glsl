/**
    Cucca Game Engine - TerrainDemo - TCS_Terrain.glsl

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#version 420 core

// define the number of CPs in the output patch
layout(vertices = 16) out;

// attributes of the input CPs
layout(location = 0) in vec4 in_TCS_position[];
layout(location = 1) in vec3 in_TCS_texCoord[];
layout(location = 2) in vec3 in_TCS_normal[];


out vec3 in_TES_CP_position[];
patch out vec3 in_TES_texCoord[4];
patch out vec3 in_TES_normal[4];


uniform vec3 cameraWorldPosition;


float getTessLevel(float dis1, float dis2) {
    float avgDis = (dis1 + dis2) * 0.5;

    if (avgDis > 64.0)
        return 512.0 / avgDis;
    else
        return 8.0;
}

inline vec3 projToPlane(vec3 v, vec3 n, vec3 p) {
    return p+n*dot(n, v-p);
}

void main() {

    //gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;

    switch (gl_InvocationID) {
    case 0:
        in_TES_CP_position[gl_InvocationID] = in_TCS_position[0].xyz;
    break;
    case 1:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[0].xyz, in_TCS_normal[0], (in_TCS_position[0].xyz+in_TCS_position[1].xyz)*0.5);
    break;
    case 2:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[1].xyz, in_TCS_normal[1], (in_TCS_position[0].xyz+in_TCS_position[1].xyz)*0.5);
    break;
    case 3:
        in_TES_CP_position[gl_InvocationID] = in_TCS_position[1].xyz;
    break;
    case 4:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[0].xyz, in_TCS_normal[0], (in_TCS_position[0].xyz+in_TCS_position[2].xyz)*0.5);
    break;
    case 5:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[0].xyz, in_TCS_normal[0], (in_TCS_position[0].xyz+in_TCS_position[1].xyz+in_TCS_position[2].xyz+in_TCS_position[3].xyz)*0.25);
    break;
    case 6:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[1].xyz, in_TCS_normal[1], (in_TCS_position[0].xyz+in_TCS_position[1].xyz+in_TCS_position[2].xyz+in_TCS_position[3].xyz)*0.25);
    break;
    case 7:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[1].xyz, in_TCS_normal[1], (in_TCS_position[1].xyz+in_TCS_position[3].xyz)*0.5);
    break;
    case 8:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[2].xyz, in_TCS_normal[2], (in_TCS_position[0].xyz+in_TCS_position[2].xyz)*0.5);
    break;
    case 9:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[2].xyz, in_TCS_normal[2], (in_TCS_position[0].xyz+in_TCS_position[1].xyz+in_TCS_position[2].xyz+in_TCS_position[3].xyz)*0.25);
    break;
    case 10:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[3].xyz, in_TCS_normal[3], (in_TCS_position[0].xyz+in_TCS_position[1].xyz+in_TCS_position[2].xyz+in_TCS_position[3].xyz)*0.25);
    break;
    case 11:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[3].xyz, in_TCS_normal[3], (in_TCS_position[1].xyz+in_TCS_position[3].xyz)*0.5);
    break;
    case 12:
        in_TES_CP_position[gl_InvocationID] = in_TCS_position[2].xyz;
    break;
    case 13:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[2].xyz, in_TCS_normal[2], (in_TCS_position[2].xyz+in_TCS_position[3].xyz)*0.5);
    break;
    case 14:
        in_TES_CP_position[gl_InvocationID] = projToPlane(in_TCS_position[3].xyz, in_TCS_normal[3], (in_TCS_position[2].xyz+in_TCS_position[3].xyz)*0.5);
    break;
    case 15:
        in_TES_CP_position[gl_InvocationID] = in_TCS_position[3].xyz;
    break;
    }

    for (int i=0; i<4; ++i) {
        in_TES_texCoord[i] = in_TCS_texCoord[i];
        in_TES_normal[i] = in_TCS_normal[i];
    }
/*
        for (int j=0; j<4; ++j)
            for (int i=0; i<4; ++i)
                in_TES_CP_position[4*i+j] = vec3(0.0, 0.0, 0.0);

        in_TES_CP_position[0] = in_TCS_position[0].xyz;
        in_TES_CP_position[3] = in_TCS_position[1].xyz;
        in_TES_CP_position[12] = in_TCS_position[2].xyz;
        in_TES_CP_position[15] = in_TCS_position[3].xyz;

        // Some dummy positions for additional control points for now
        in_TES_CP_position[1] = in_TCS_position[0].xyz + vec3(0.0, 10.0, 0.0);
        in_TES_CP_position[2] = in_TCS_position[1].xyz + vec3(0.0, 10.0, 0.0);
        in_TES_CP_position[13] = in_TCS_position[2].xyz + vec3(0.0, 10.0, 0.0);
        in_TES_CP_position[14] = in_TCS_position[3].xyz + vec3(0.0, 10.0, 0.0);
        in_TES_CP_position[4] = in_TES_CP_position[1];
        in_TES_CP_position[5] = in_TES_CP_position[1];
        in_TES_CP_position[6] = in_TES_CP_position[2];
        in_TES_CP_position[7] = in_TES_CP_position[2];
        in_TES_CP_position[8] = in_TES_CP_position[13];
        in_TES_CP_position[9] = in_TES_CP_position[13];
        in_TES_CP_position[10] = in_TES_CP_position[14];
        in_TES_CP_position[11] = in_TES_CP_position[14];*/


    // Calculate the distance from the camera to the three control points
    vec4 camDis = vec4( distance(cameraWorldPosition, in_TCS_position[0].xyz),
                        distance(cameraWorldPosition, in_TCS_position[1].xyz),
                        distance(cameraWorldPosition, in_TCS_position[2].xyz),
                        distance(cameraWorldPosition, in_TCS_position[3].xyz) );

    // Calculate the tessellation levels
    gl_TessLevelOuter[0] = getTessLevel(camDis[0], camDis[2]);
    gl_TessLevelOuter[1] = getTessLevel(camDis[0], camDis[1]);
    gl_TessLevelOuter[2] = getTessLevel(camDis[1], camDis[3]);
    gl_TessLevelOuter[3] = getTessLevel(camDis[2], camDis[3]);
    gl_TessLevelInner[0] = min(gl_TessLevelOuter[0], gl_TessLevelOuter[1]);
    gl_TessLevelInner[1] = gl_TessLevelInner[0];
}
