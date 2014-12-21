/**
    Cucca Game Engine - Core - ShaderObject.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-21
**/


#include "../../include/Graphics/ShaderObject.hpp"


using namespace Cucca;


void ShaderObject::init(const ResourceInitInfo<ShaderObject>& initInfo,
                        const std::vector<ResourceId>& initResources,
                        const std::vector<ResourceId>& depResources,
                        ResourceManager<ResourceId>* resourceManager) {
    switch (initInfo.source) {
    case ResourceInitInfo<ShaderObject>::SOURCE_CODE:
        if (initResources.size() == 0) {
            objectId_ = 0;
            return;
        }

        //auto src = resourceManager->getResource<Binary>(initResources[0]);

        objectId_ = glCreateShader(initInfo.type);


    break;
    case ResourceInitInfo<ShaderObject>::SOURCE_BINARY:
        throw "ShaderObject: binary loading not implemented"; // TODO_EXCEPTION: throw a proper exception
    break;
    }
}

void ShaderObject::destroy(void) {
    if (objectId_ != 0)
        glDeleteShader(objectId_);
}
