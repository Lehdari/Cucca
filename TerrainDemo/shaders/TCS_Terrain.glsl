/**
    Cucca Game Engine - TerrainDemo - TCS_Terrain.glsl

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-19
**/


#version 400 core

// define the number of CPs in the output patch
layout(vertices = 4) out;

// attributes of the input CPs
in vec4 in_TCS_position[];
in vec3 in_TCS_texCoord[];
in vec3 in_TCS_normal[];

// attributes of the output CPs
out vec4 in_TES_position[];
out vec3 in_TES_texCoord[];
out vec3 in_TES_normal[];


uniform vec3 cameraWorldPosition;


float getTessLevel(float dis1, float dis2) {
    float avgDis = (dis1 + dis2) * 0.5;

    if (avgDis > 64.0)
        return 512.0 / avgDis;
    else
        return 8.0;
}


void main() {
    // Set the control points of the output patch
    in_TES_position[gl_InvocationID] = in_TCS_position[gl_InvocationID];
    in_TES_texCoord[gl_InvocationID] = in_TCS_texCoord[gl_InvocationID];
    in_TES_normal[gl_InvocationID] = in_TCS_normal[gl_InvocationID];

    // Calculate the distance from the camera to the three control points
    float EyeToVertexDistance0 = distance(cameraWorldPosition, in_TES_position[0].xyz);
    float EyeToVertexDistance1 = distance(cameraWorldPosition, in_TES_position[1].xyz);
    float EyeToVertexDistance2 = distance(cameraWorldPosition, in_TES_position[2].xyz);
    float EyeToVertexDistance3 = distance(cameraWorldPosition, in_TES_position[3].xyz);

    // Calculate the tessellation levels
    gl_TessLevelOuter[0] = getTessLevel(EyeToVertexDistance0, EyeToVertexDistance1);
    gl_TessLevelOuter[1] = getTessLevel(EyeToVertexDistance1, EyeToVertexDistance2);
    gl_TessLevelOuter[2] = getTessLevel(EyeToVertexDistance2, EyeToVertexDistance3);
    gl_TessLevelOuter[3] = getTessLevel(EyeToVertexDistance3, EyeToVertexDistance0);
    gl_TessLevelInner[0] = gl_TessLevelOuter[2];
    gl_TessLevelInner[1] = gl_TessLevelOuter[2];
}
