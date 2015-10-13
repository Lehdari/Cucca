/**
    Cucca Game Engine - Graphics - Camera.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-10-11
**/


#ifndef CUCCA_GRAPHICS_CAMERA_HPP
#define CUCCA_GRAPHICS_CAMERA_HPP


#include <Cucca/Core/MathTypes.hpp>


namespace Cucca {

    class Camera {
    public:
        Camera(const Vector3Glf& position, const Vector3Glf& forward, const Vector3Glf& up,
               float fov, float aspectRatio, float near, float far);
        Camera(void);

        void lookAt(const Vector3Glf& from, const Vector3Glf& to, const Vector3Glf& up);
        void lookAt(Vector3Glf&& from, Vector3Glf&& to, Vector3Glf&& up);
        void projection(float fov, float aspectRatio, float near, float far);

        const Vector3Glf& getPosition(void) const;

    protected:
        //  Vectors for orientation matrix
        Vector3Glf position_;
        Vector3Glf forward_;
        Vector3Glf up_;

        //  Values for projection matrix
        float fov_;
        float aspectRatio_;
        float near_;
        float far_;

        //  Quaternion and matrices calculated from members above
        QuaternionGlf rotationQ_;
        Matrix4Glf orientation_;
        Matrix4Glf projection_;

        //  Member function for updating the orientation
        void updateOrientation(void);
    };

}   //  namespace Cucca


#endif // CUCCA_GRAPHICS_CAMERA_HPP
