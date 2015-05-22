/**
    Cucca Game Engine - Graphics - ShaderObject.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-08
**/


#include "../../include/Graphics/ShaderProgram.hpp"


using namespace Cucca;


ShaderProgram::ShaderProgram(void) :
    programId_(0)
{}

GLuint ShaderProgram::getId(void) const {
    return programId_;
}
