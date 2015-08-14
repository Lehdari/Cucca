/**
    Cucca Game Engine - Debug - Debug.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    Header file for debugging purposes. It uses macros so


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-12
**/


#ifndef CUCCA_DEBUG_DEBUG_HPP
#define CUCCA_DEBUG_DEBUG_HPP


#ifdef CUCCA_DEBUG


//  Print formatted output
#define CUCCA_DPRINTF(format, ...) Cucca::debugPrintFormat(format, true, ##__VA_ARGS__);

//  Print single variable output
#define CUCCA_DPRINTS(var) Cucca::debugPrintSingle(#var, var);


#include "Print.hpp"
#include "Time.hpp"


#else   //  CUCCA_DEBUG


#define CUCCA_DPRINTF(fstr, params...)


#endif  //  CUCCA_DEBUG


#endif //  CUCCA_DEBUG_DEBUG_HPP
