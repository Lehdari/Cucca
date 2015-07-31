/**
    Cucca Game Engine - Debug - Time.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-24
**/


#ifndef CUCCA_DEBUG_TIME_HPP
#define CUCCA_DEBUG_TIME_HPP


#include <vector>
#include <chrono>


namespace Cucca {

    namespace Debug {

        class ClockSequence {
        public:
            static void begin(size_t reserve = 2u);
            static void point(void);
            static void end(void);

        private:
            static std::vector<std::chrono::steady_clock::time_point> sequence__;
        };

    };  //  namespace Debug

};  //  namespace Cucca


#endif // CUCCA_DEBUG_TIME_HPP
