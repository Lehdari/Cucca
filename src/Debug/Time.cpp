/**
    Cucca Game Engine - Debug - Time.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-05-24
**/


#include <Cucca/Debug/Time.hpp>

#include <cstdio>


using namespace Cucca::Debug;


std::vector<std::chrono::steady_clock::time_point> ClockSequence::sequence__ = std::vector<std::chrono::steady_clock::time_point>();


void ClockSequence::begin(size_t reserve) {
    sequence__.clear();
    sequence__.reserve(reserve);
    sequence__.push_back(std::chrono::steady_clock::now());
}

void ClockSequence::point(void) {
    sequence__.push_back(std::chrono::steady_clock::now());
}

void ClockSequence::end(void) {
    sequence__.push_back(std::chrono::steady_clock::now());

    if (sequence__.size() < 2)
        return;

    for (auto i=1u; i<sequence__.size(); ++i) {
        printf("point %u - point %u: %llims\n", i-1, i,
               std::chrono::duration_cast<std::chrono::milliseconds>(sequence__[i]-sequence__[i-1]).count());
    }
}
