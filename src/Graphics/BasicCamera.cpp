/**
    Cucca Game Engine - Graphics - BasicCamera.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-09
**/


#include "../../include/Graphics/BasicCamera.hpp"


using namespace Cucca;


BasicCamera::BasicCamera(void) {
    orientation_ << 1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1;

    perspective_ << 1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1;
}

void BasicCamera::nodeEnter(Node* node, MeshComponent* component) {

}

void BasicCamera::nodeExit(Node* node, MeshComponent* component) {

}
