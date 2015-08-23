/**
    Cucca Game Engine - Core - MathUtils.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-23
**/


#ifndef CUCCA_CORE_MATHUTILS_HPP
#define CUCCA_CORE_MATHUTILS_HPP


namespace Cucca {

    ///  Functions

    template<typename T, int W, int H>
    void clamp(Eigen::Matrix<T, W, H, Eigen::DontAlign>& matrix, const T& min, const T& max);


    ///  Function definitions

    //  Clamps all values in given matrix in range specified
    template<typename T, int W, int H>
    void clamp(Eigen::Matrix<T, W, H, Eigen::DontAlign>& matrix, const T& min, const T& max) {
        for (auto x=0; x<W; ++x)
            for (auto y=0; y<H; ++y)
                if (matrix(x, y) < min)
                    matrix(x, y) = min;
                else if (matrix(x, y) > max)
                    matrix(x, y) = max;
    }

}   //  namespace Cucca


#endif  //  CUCCA_CORE_MATHUTILS_HPP
