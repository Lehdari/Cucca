/**
    Cucca Game Engine - Core - Platform.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-12
**/


#include <Cucca/Core/Platform.hpp>


#ifdef _WIN32 // Windows (32-bit and 64-bit, this part is common)

    #include <windows.h>

    bool Cucca::threadHasGlContext(void) {
        return (wglGetCurrentContext() == NULL) ? false : true;
    }

    #ifdef _WIN64 // Windows (64-bit only)
    #endif

#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_IPHONE_SIMULATOR // iOS Simulator

        bool Cucca::threadHasGlContext(void) {
            return (eglGetCurrentContext() == EGL_NO_CONTEXT) ? false : true;
        }

    #elif TARGET_OS_IPHONE // iOS device

        bool Cucca::threadHasGlContext(void) {
            return (eglGetCurrentContext() == EGL_NO_CONTEXT) ? false : true;
        }

    #elif TARGET_OS_MAC // Other kinds of Mac OS

        bool Cucca::threadHasGlContext(void) {
            return (aglGetCurrentContext() == NULL) ? false : true;
        }

    #else // Unsupported platform
        #error "Unsupported platform"
    #endif
#elif __linux // Linux

    bool Cucca::threadHasGlContext(void) {
        return (glxGetCurrentContext() == NULL) ? false : true;
    }

#elif __unix // All unices not caught above

    bool Cucca::threadHasGlContext(void) {
        return (glxGetCurrentContext() == NULL) ? false : true;
    }

#elif __posix // POSIX

    bool Cucca::threadHasGlContext(void) {
        return (glxGetCurrentContext() == NULL) ? false : true;
    }

#else
    #error "Unsupported platform"

#endif
