#ifndef CUCCA_UNITTESTS_UNITTEST2_HPP
#define CUCCA_UNITTESTS_UNITTEST2_HPP


#include "UnitTests.hpp"


#if CURRENT_TEST == 2


#include <Cucca/Core/Event.hpp>


struct TestEvent1 {
    unsigned a_;
};

struct TestEvent2 {
    unsigned b_;
};


int unitTest(void);


#endif // CURRENT_TEST


#endif // CUCCA_UNITTESTS_UNITTEST2_HPP
