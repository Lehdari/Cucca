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
#include <atomic>
#include <unordered_map>
#include <queue>
#include <vector>


namespace Cucca {

    class ThreadPool {
    public:
        enum Status {
            STATUS_INITIALIZED,
            STATUS_RUNNING,
            STATUS_TERMINATING,
            STATUS_TERMINATED
        };

        ThreadPool(void);
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool(ThreadPool&&) = delete;

        ~ThreadPool(void);

        ThreadPool operator=(const ThreadPool&) = delete;
        ThreadPool operator=(ThreadPool&&) = delete;

        void launchThreads(unsigned n);
        void joinThreads(unsigned n);

        void terminate(void);

        void pushTask(const Task& task);
        void pushTask(Task&& task);

        unsigned threadsPerformingTask(void);

    private:
        // loop for worker threads
        void loop(void);

        Status status_;

        std::unordered_map<std::thread::id, std::thread> threads_;
        std::atomic_uint threadsToJoin_; // for signaling threads to join
        std::vector<std::thread::id> threadsJoining_; // for joining threads to tell their ids
        std::mutex threadsJoiningMutex_; // for use with condition variable
        std::condition_variable threadsJoiningCV_; // for threads to signal they're joining

        std::queue<Task> tasks_;
        std::atomic_uint threadsPerformingTask_;
        std::mutex taskMutex_;
        std::condition_variable taskCV_;
    };


    //  Member definitions
    ThreadPool::ThreadPool(void) :
        status_(STATUS_INITIALIZED),
        threadsToJoin_(0),
        threadsPerformingTask_(0)
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

        for (auto i=0u; i<n; ++i) {
            std::thread t(&ThreadPool::loop, this);
            threads_.insert(std::make_pair(t.get_id(), std::move(t)));
        }
    }

    void ThreadPool::joinThreads(unsigned n) {
        threadsToJoin_ = n;
        taskCV_.notify_all();

        std::unique_lock<std::mutex> lock(threadsJoiningMutex_);
        threadsJoiningCV_.wait(lock, [this] { return threadsToJoin_ == 0; });

        for (auto& threadID : threadsJoining_) {
            threads_[threadID].join();
            threads_.erase(threadID);
        }

        threadsJoining_.clear();
    }

    void ThreadPool::terminate(void) {
        taskMutex_.lock();
        status_ = STATUS_TERMINATING;
        taskMutex_.unlock();
        taskCV_.notify_all();

        for (auto& thread : threads_)
            if (thread.second.joinable())
                thread.second.join();

        threads_.clear();
    }

    void ThreadPool::pushTask(const Task& task) {
        {
            std::lock_guard<std::mutex> lock(taskMutex_);
            tasks_.push(task);
        }
        taskCV_.notify_one();
    }

    void ThreadPool::pushTask(Task&& task) {
        {
            std::lock_guard<std::mutex> lock(taskMutex_);
            tasks_.push(task);
        }
        taskCV_.notify_one();
    }

    unsigned ThreadPool::threadsPerformingTask(void) {
        return threadsPerformingTask_;
    }

    void ThreadPool::loop(void) {
        while (status_ == STATUS_RUNNING) {
            std::unique_lock<std::mutex> lock(taskMutex_);
            // wait for notification
            taskCV_.wait(lock, [this] { return tasks_.size() > 0 ||
                                               status_ == STATUS_TERMINATING ||
                                               threadsToJoin_ > 0; });

            if (status_ == STATUS_TERMINATING)
                break;

            if (threadsToJoin_ > 0) {
                {
                    std::lock_guard<std::mutex> lock2(threadsJoiningMutex_);
                    threadsJoining_.push_back(std::this_thread::get_id());
                }
                --threadsToJoin_;
                threadsJoiningCV_.notify_all();
                return;
            }

            Task task(tasks_.front());
            tasks_.pop();

            lock.unlock(); // end of synchronization

            ++threadsPerformingTask_;
            task.run();
            --threadsPerformingTask_;
        }
    }

} // namespace Cucca


#endif // CUCCA_CORE_THREADPOOL_HPP
