/**
    Cucca Game Engine - Graphics - VertexData.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-27
**/


#include "../../include/Graphics/VertexData.hpp"
#include "../../include/Core/ResourceManager.hpp"
#include "../../include/Core/Binary.hpp"
#include "../../include/Core/StorageVector.hpp"

#include <cstring>


using namespace Cucca;


void VertexData::init(const ResourceInitInfo<VertexData>& initInfo,
                      const std::vector<ResourceId>& initResources,
                      const std::vector<ResourceId>& depResources,
                      ResourceManager<ResourceId>* resourceManager) {
    switch (initInfo.source) {
    case ResourceInitInfo<VertexData>::SOURCE_BINARY_OBJ:
        {
            if (initResources.size() == 0)
                return;

            char* buffer = resourceManager->getResource<Binary>(initResources[0])->getBufferPtr();
            for (auto i=0u; i<30; ++i)
                printf("%c", buffer[i]);
            printf("\n");

            char spec[32];

            printf("buffer size: %u\n", strlen(buffer));

            std::vector<StorageVector<float, 4>> positions;
            std::vector<StorageVector<float, 4>> texCoords;
            std::vector<StorageVector<float, 3>> normals;
            std::vector<StorageVector<float, 3, 3>> indices;

            while(*buffer) {
                if (sscanf(buffer, "%s", spec) == 0)
                    return;

                printf("spec length: %u\n", strlen(spec));
                printf("spec[0]: %c\n", spec[0]);
                printf("spec[1]: %c\n", spec[1]);

                buffer += strlen(spec)+1;

                switch (spec[0]) {
                case 'v':
                    switch(spec[1]) {
                    case 't':
                        {
                            Eigen::Vector3f texCoord;
                            texCoord << 0.0f, 0.0f, 0.0f;
                            if (sscanf(buffer, "%f %f %f", &texCoord(0), &texCoord(1), &texCoord(2)) < 2)
                                throw "VertexData: invalid file!"; // TODO_EXCEPTION
                            texCoords.push_back(texCoord);
                        }
                    break;
                    case 'n':
                        {
                            Eigen::Vector3f normal;
                            normal << 0.0f, 0.0f, 0.0f;
                            if (sscanf(buffer, "%f %f %f", &normal(0), &normal(1), &normal(2)) < 3)
                                throw "VertexData: invalid file!"; // TODO_EXCEPTION
                            normals.push_back(normal);
                        }
                    break;
                    case 'p':
                        throw "VertexData: parameter space vertex loading from .obj file not supported!"; // TODO_EXCEPTION
                    break;
                    default:
                        {
                            Eigen::Vector4f position;
                            position << 0.0f, 0.0f, 0.0f, 1.0f;
                            if (sscanf(buffer, "%f %f %f %f", &position(0), &position(1), &position(2), &position(3)) < 3)
                                throw "VertexData: invalid file!"; // TODO_EXCEPTION
                            positions.push_back(position);
                            printf("Another bytes the dust\n");
                        }
                    break;
                    }
                break;
                case 'f':
                    {
                        Eigen::Matrix3i index;
                        index << 0, 0, 0,  0, 0, 0,  0, 0, 0;
                        if (sscanf(buffer, "%u/%u/%u %u/%u/%u %u/%u/%u", &index(0,0), &index(1,0), &index(2,0), &index(0,1), &index(1,1), &index(2,1), &index(0,2), &index(1,2), &index(2,2)) < 9 ||
                            sscanf(buffer, "%u//%u %u//%u %u//%u", &index(0,0), &index(2,0), &index(0,1), &index(2,1), &index(0,2), &index(2,2)) < 6 ||
                            sscanf(buffer, "%u/%u %u/%u %u/%u", &index(0,0), &index(1,0), &index(0,1), &index(1,1), &index(0,2), &index(1,2)) < 6 ||
                            sscanf(buffer, "%u %u %u", &index(0,0), &index(0,1), &index(0,2)) < 3)
                            throw "VertexData: invalid file!"; // TODO_EXCEPTION
                        indices.push_back(index);
                    }
                break;
                default:
                break;
                }

                while (*buffer++ != 10)
                    printf("%c", *buffer);
            }

            printf("Read %u positions, %u texture coordinates, %u normals and %u indices\n", positions.size(), texCoords.size(), normals.size(), indices.size()); // TEMP
        }
    break;
    }
}

void VertexData::destroy(void) {

}
