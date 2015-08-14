/**
    Cucca Game Engine - Debug - Print.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.


    This file defines debug printing interface for threaded environment.


    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-08-12
**/


#ifndef CUCCA_DEBUG_PRINT_HPP
#define CUCCA_DEBUG_PRINT_HPP


#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <mutex>


namespace Cucca {

    //  Mutex preventing output tearing
    extern std::recursive_mutex debugPrintMutex;


    //  Prefix with thread and time info
    std::string debugPrintPrefix(void);


    //  Formatted output
    template<typename... Params>
    void debugPrintFormat(const char* format, bool first = false, Params... params);

    template<typename T, typename... Params>
    void debugPrintFormat(const char* format, bool first, T v, Params... params);


    //  Single variable output
    template<typename T>
    void debugPrintSingle(const char* name, T v);


    //  TMP struct for formatting codes
    template<typename T>
    struct FormatString {
        static const char* value(void);
    };

    template<typename T>
    struct FormatString<T*> {
        static const char* value(void);
    };


    /// Template definitions
    template<typename T, typename... Params>
    void debugPrintFormat(const char* format, bool first, T v, Params... params) {
        std::lock_guard<std::recursive_mutex> lock(debugPrintMutex);

        if (first)
            printf(debugPrintPrefix().c_str());

        for (auto i=0u; format[i]; ++i) {
            if (format[i] == '%') {
                std::string str(format, i);
                str += FormatString<T>::value();
                printf(str.c_str(), v);
                debugPrintFormat(format+i+1, false, params...);
                return;
            }
        }

        debugPrintFormat(format);
    }

    //  specialization for string
    template<typename... Params>
    void debugPrintFormat(const char* format, bool first, const std::string& s, Params... params) {
        std::lock_guard<std::recursive_mutex> lock(debugPrintMutex);

        if (first)
            printf(debugPrintPrefix().c_str());

        for (auto i=0u; format[i]; ++i) {
            if (format[i] == '%') {
                std::string str(format, i);
                str += "%s";
                printf(str.c_str(), s.c_str());
                debugPrintFormat(format+i+1, false, params...);
                return;
            }
        }

        debugPrintFormat(format);
    }


    template<typename T>
    void debugPrintSingle(const char* name, T v) {
        std::lock_guard<std::recursive_mutex> lock(debugPrintMutex);

        std::cout << debugPrintPrefix() << name << ": " << v << std::endl;
    }


    template<typename T> const char* FormatString<T*>::value(void)      { return "%p"; }


}   //  namespace Cucca


#endif  //  CUCCA_DEBUG_PRINT_HPP
