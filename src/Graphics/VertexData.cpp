/**
    Cucca Game Engine - Graphics - VertexData.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-27
**/


#include "../../include/Graphics/VertexData.hpp"


using namespace Cucca;


void VertexData::init(const ResourceInitInfo<VertexData>& initInfo,
                      const std::vector<ResourceId>& initResources,
                      const std::vector<ResourceId>& depResources,
                      ResourceManager<ResourceId>* resourceManager) {
    switch (initInfo.source) {
    case ResourceInitInfo<VertexData>::SOURCE_BINARY_OBJ:
        {

        }
    break;
    }
}

void VertexData::destroy(void) {

}
