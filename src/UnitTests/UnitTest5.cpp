#include "../../include/UnitTests/UnitTest5.hpp"


#if CURRENT_TEST == 5


#include "../../include/Core/ThreadPool.hpp"

#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>


using namespace Cucca;


void testFunction1(void) {
    std::cout << "testFunction1() working.. " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
}

void testFunction2(void) {
    std::cout << "testFunction2() working.. " << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
}


class TestClass {
public:
    void testMemberFunction(void) {
        std::cout << "TestClass::testMemberFunction() working.. " << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
    }
};


int unitTest(void) {
    srand(time(NULL));

    TestClass test;

    Task task1(testFunction1);
    Task task2(testFunction2);
    Task task3(&test, &TestClass::testMemberFunction);

    ThreadPool pool;
    std::cout << "Launching 4 threads.. ";
    pool.launchThreads(4);
    std::cout << "done" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1)); // add a bit of wait before terminating

    unsigned n = 200 + (rand() % 200);
    std::cout << "Queueing " << n << " tasks.. " << std::endl;
    for (auto i=0u; i<n; ++i) {
        switch (rand() % 3) {
        case 0: pool.pushTask(std::move(Task(task1))); break;
        case 1: pool.pushTask(std::move(Task(task2))); break;
        case 2: pool.pushTask(std::move(Task(task3))); break;
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(10)); // add a bit of wait before terminating

    return 0;
}


#endif // CURRENT_TEST
