#include "../../include/UnitTests/UnitTest5.hpp"


#if CURRENT_TEST == 5


#include <Cucca/Core/ThreadPool.hpp>

#include <iostream>
#include <chrono>
#include <random>


using namespace Cucca;


std::default_random_engine r;


void testFunction1(void) {
    unsigned time = r() % 500;
    std::cout << "thread " << std::this_thread::get_id() << ": testFunction1 working for " << time << "ms\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}

void testFunction2(int a, float b) {
    unsigned time = r() % 500;
    std::cout << "thread " << std::this_thread::get_id() << ": testFunction2 working for " << time << "ms with parameters a=" << a << " , b=" << b << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
}


class TestClass {
public:
    void testMemberFunction1(void) {
        unsigned time = r() % 500;
        std::cout << "thread " << std::this_thread::get_id() << ": TestClass::testMemberFunction1 working for " << time << "ms\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }

    void testMemberFunction2(int a, float b) {
        unsigned time = r() % 500;
        std::cout << "thread " << std::this_thread::get_id() << ": TestClass::testMemberFunction2 working for " << time << "ms with parameters a=" << a << " , b=" << b << "\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }

    void testMemberFunction3(const std::string& s) {
        unsigned time = r() % 500;
        std::cout << "thread " << std::this_thread::get_id() << ": TestClass::testMemberFunction3 working for " << time << "ms with parameters s=\"" << s << "\"\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(time));
    }
};


int unitTest(void) {
    TestClass test;
    std::string testStr("kaka pyly");

    Task task1(testFunction1);
    Task task2(testFunction2, 45, 3.2f);
    Task task3(&test, &TestClass::testMemberFunction1);
    Task task4(&test, &TestClass::testMemberFunction2, 100, 56.3f);
    Task task5(&test, &TestClass::testMemberFunction3, testStr);

    ThreadPool pool;
    std::cout << "Launching 2 threads\n";
    pool.launchThreads(4);
    std::cout << "Joining 2 threads\n";
    pool.joinThreads(2);

    unsigned n = 140 + (r() % 10);
    std::cout << "Queueing " << n << " tasks\n";
    for (auto i=0u; i<n; ++i) {
        switch (r() % 5) {
        case 0: pool.pushTask(task1); break;
        case 1: pool.pushTask(task2); break;
        case 2: pool.pushTask(task3); break;
        case 3: pool.pushTask(task4); break;
        case 4: pool.pushTask(task5); break;
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
