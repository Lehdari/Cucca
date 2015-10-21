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


//#include "CMakeConfig.hpp"


#ifdef CUCCA_DEBUG

    #warning Building debug target

    //  Print formatted output
    #define CUCCA_DPRINTF(FORMAT, ...) Cucca::debugPrintFormat(FORMAT, true, ##__VA_ARGS__);

    //  Print single variable output
    #define CUCCA_DPRINTS(VAR) Cucca::debugPrintSingle(#VAR, VAR);


    #include <Cucca/Debug/Print.hpp>
    #include <Cucca/Debug/Time.hpp>

#else   //  CUCCA_DEBUG

    #define CUCCA_DPRINTF(fstr, params...)

#endif  //  CUCCA_DEBUG


#endif //  CUCCA_DEBUG_DEBUG_HPP
