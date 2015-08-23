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


#include <Eigen/Dense>


namespace Cucca {

    ///  Functions

    //  Clamps all values in given matrix in range specified
    template<typename T, int W, int H>
    inline void clamp(Eigen::Matrix<T, W, H, Eigen::DontAlign>& matrix, const T& min, const T& max);

    //  Cubic(and bicubic) interpolation, provide d for derivative
    template<typename T>
    T cubicInterpolate(const T (&p)[4], float t, T* d = nullptr);
    template<typename T>
    T bicubicInterpolate(const T (&p)[4][4], float x, float y, T* dx = nullptr, T* dy = nullptr);


    ///  Function definitions

    template<typename T, int W, int H>
    void clamp(Eigen::Matrix<T, W, H, Eigen::DontAlign>& matrix, const T& min, const T& max) {
        for (auto x=0; x<W; ++x)
            for (auto y=0; y<H; ++y)
                if (matrix(x, y) < min)
                    matrix(x, y) = min;
                else if (matrix(x, y) > max)
                    matrix(x, y) = max;
    }

    template<typename T>
    T cubicInterpolate(const T (&p)[4], float t, T* d) {
        if (d)
            *d = 0.5*(p[2] - p[0]) + t*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + t*(-1.5*p[0] + 4.5*(p[1] - p[2]) + 1.5*p[3]));
        return p[1] + 0.5 * t*(p[2] - p[0] + t*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + t*(3.0*(p[1] - p[2]) + p[3] - p[0])));
    }

    template<typename T>
    T bicubicInterpolate(const T (&p)[4][4], float x, float y, T* dx, T* dy) {
        T arr[4];
        T arrDy[4]{};
        for (auto i=0u; i<4; ++i)
            if (dy)
                arr[i] = cubicInterpolate(p[i], y, &arrDy[i]);
            else
                arr[i] = cubicInterpolate(p[i], y);

        if (dy)
            *dy = cubicInterpolate(arrDy, x);
        return cubicInterpolate(arr, x, dx);
    }

}   //  namespace Cucca


#endif  //  CUCCA_CORE_MATHUTILS_HPP
