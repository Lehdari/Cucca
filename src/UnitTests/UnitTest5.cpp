#include "../../include/UnitTests/UnitTest5.hpp"


#if CURRENT_TEST == 5


#include "../../include/Core/ThreadPool.hpp"

#include <iostream>
#include <chrono>
#include <random>


using namespace Cucca;


std::default_random_engine r;


void testFunction1(void) {
    unsigned time = r() % 500;
    std::cout << "thread " << std::this_thread::get_id() << ": testFunction1() working for " << time << "ms\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void testFunction2(void) {
    unsigned time = r() % 500;
    std::cout << "thread " << std::this_thread::get_id() << ": testFunction2() working for " << time << "ms\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}


class TestClass {
public:
    void testMemberFunction(void) {
        unsigned time = r() % 500;
        std::cout << "thread " << std::this_thread::get_id() << ": TestClass::testMemberFunction() working for " << time << "ms\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }
};


int unitTest(void) {
    TestClass test;

    Task task1(testFunction1);
    Task task2(testFunction2);
    Task task3(&test, &TestClass::testMemberFunction);

    ThreadPool pool;
    std::cout << "Launching 2 threads\n";
    pool.launchThreads(4);
    std::cout << "Joining 2 threads\n";
    pool.joinThreads(2);

    unsigned n = 140 + (r() % 10);
    std::cout << "Queueing " << n << " tasks\n";
    for (auto i=0u; i<n; ++i) {
        switch (r() % 3) {
        case 0: pool.pushTask(std::move(Task(task1))); break;
        case 1: pool.pushTask(std::move(Task(task2))); break;
        case 2: pool.pushTask(std::move(Task(task3))); break;
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Launching 2 threads\n";
    pool.launchThreads(2);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Launching 2 threads\n";
    pool.launchThreads(2);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Launching 2 threads\n";
    pool.launchThreads(2);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Joining 2 threads\n";
    pool.joinThreads(2);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Joining 2 threads\n";
    pool.joinThreads(2);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout << "Joining 2 threads\n";
    pool.joinThreads(2);

    std::this_thread::sleep_for(std::chrono::seconds(5)); // add a bit of wait before terminating

    return 0;
}


#endif // CURRENT_TEST
