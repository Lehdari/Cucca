/**
    Cucca Game Engine - Core - ThreadPool.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-11-22
**/


#ifndef CUCCA_CORE_THREADPOOL_HPP
#define CUCCA_CORE_THREADPOOL_HPP


#include "Task.hpp"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <iostream> //TEMP


namespace Cucca {

    class ThreadPool { // TODO_RO3
    public:
        enum Status {
            STATUS_INITIALIZED,
            STATUS_RUNNING,
            STATUS_TERMINATING,
            STATUS_TERMINATED
        };

        ThreadPool(void);
        ~ThreadPool(void);

        void launchThreads(unsigned n);
        void destroyThreads(unsigned n);

        void terminate(void);

        //void pushTask(const Task& task);
        void pushTask(Task&& task);

    private:
        Task pullTask(void);
        // loop for worker threads
        void loop(void);

        Status status_;

        std::vector<std::thread> threads_;

        std::queue<Task> tasks_;
        std::mutex taskMutex_;
        std::condition_variable taskCV_;
    };


    //  Member definitions
    ThreadPool::ThreadPool(void) :
        status_(STATUS_INITIALIZED)
    {}

    ThreadPool::~ThreadPool(void) {
        if (status_ == STATUS_RUNNING)
            terminate();
    }

    void ThreadPool::launchThreads(unsigned n) {
        if (n == 0)
            return;

        if (status_ == STATUS_INITIALIZED)
            status_ = STATUS_RUNNING;

        for (auto i=0u; i<n; ++i)
            threads_.emplace_back(&ThreadPool::loop, this);
    }

    void ThreadPool::destroyThreads(unsigned n) {
        for (auto i=0u; i<n || threads_.size() > 0; ++i) {
            if (threads_.back().joinable())
                threads_.back().join();
            threads_.pop_back();
        }
    }

    void ThreadPool::terminate(void) {
        std::cout << "terminating.. " << std::endl;
        taskMutex_.lock();
        status_ = STATUS_TERMINATING;
        taskMutex_.unlock();
        std::cout << "notifying threads.. " << std::endl;
        taskCV_.notify_all();

        for (auto& thread : threads_)
            if (thread.joinable())
                thread.join();
        std::cout << "all threads joined" << std::endl;

        threads_.clear();
    }

    void ThreadPool::pushTask(Task&& task) {
        {
            //std::lock_guard<std::mutex> lock(taskMutex_);
            taskMutex_.lock();
            tasks_.push(task);
            taskMutex_.unlock();
            //std::cout << "pushed, tasks_.size(): " << tasks_.size() << std::endl;
        }
        taskCV_.notify_one();
    }

    Task ThreadPool::pullTask(void) {
        Task task(tasks_.front());
        tasks_.pop();
        //std::cout << "popped, tasks_.size(): " << tasks_.size() << std::endl;
        return task;
    }

    void ThreadPool::loop(void) {
        while (status_ == STATUS_RUNNING) {
            std::unique_lock<std::mutex> lock(taskMutex_);
            //std::cout << "thread " << std::this_thread::get_id() << ": waiting for notification" << std::endl;
            taskCV_.wait(lock, [this]{ return tasks_.size() > 0 || status_ == STATUS_TERMINATING; }); // wait for notification
            //std::cout << "thread " << std::this_thread::get_id() << ": notification received" << std::endl;

            if (status_ == STATUS_TERMINATING)
                break;

            Task task = pullTask();
            lock.unlock(); // no more critical use of tasks_ queue

            task.run();
        }
    }

} // namespace Cucca


#endif // CUCCA_CORE_THREADPOOL_HPP
