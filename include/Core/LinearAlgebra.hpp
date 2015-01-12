/**
    Cucca Game Engine - Core - LinearAlgebra.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    This file defines typedefs to linear algebra library used (currently Eigen 3)

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-10
**/

#ifndef CUCCA_CORE_LINEARALGEBRA_HPP
#define CUCCA_CORE_LINEARALGEBRA_HPP


#include <Eigen/Dense>
#include <GL/glew.h>


namespace Cucca {

    typedef Eigen::Matrix<float, 2, 1, Eigen::DontAlign> Vector2f;
    typedef Eigen::Matrix<float, 3, 1, Eigen::DontAlign> Vector3f;
    typedef Eigen::Matrix<float, 4, 1, Eigen::DontAlign> Vector4f;

    typedef Eigen::Matrix<float, 2, 2, Eigen::DontAlign> Matrix2f;
    typedef Eigen::Matrix<float, 3, 3, Eigen::DontAlign> Matrix3f;
    typedef Eigen::Matrix<float, 4, 4, Eigen::DontAlign> Matrix4f;

    typedef Eigen::Matrix<GLfloat, 2, 1, Eigen::DontAlign> Vector2Glf;
    typedef Eigen::Matrix<GLfloat, 3, 1, Eigen::DontAlign> Vector3Glf;
    typedef Eigen::Matrix<GLfloat, 4, 1, Eigen::DontAlign> Vector4Glf;

    typedef Eigen::Matrix<GLfloat, 2, 2, Eigen::DontAlign> Matrix2Glf;
    typedef Eigen::Matrix<GLfloat, 3, 3, Eigen::DontAlign> Matrix3Glf;
    typedef Eigen::Matrix<GLfloat, 4, 4, Eigen::DontAlign> Matrix4Glf;

} // namespace Cucca


#endif // CUCCA_CORE_LINEARALGEBRA_HPP
