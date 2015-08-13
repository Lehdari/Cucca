/**
    Cucca Game Engine - Core - ThreadPool.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-21
**/


#include "../../include/Core/ThreadPool.hpp"


using namespace Cucca;


ThreadPool::ThreadPool(void) :
    status_(STATUS_INITIALIZED),
    threadsToJoin_(0),
    tasks_(&taskCV_),
    threadsPerformingTask_(0)
{}

ThreadPool::~ThreadPool(void) {
    if (status_ == STATUS_RUNNING)
        terminate();
}

void ThreadPool::launchThreads(unsigned n) {
    if (n == 0)
        return;

    if (status() == STATUS_INITIALIZED)
        setStatus(STATUS_RUNNING);

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
    setStatus(STATUS_TERMINATING);

    taskCV_.notify_all();

    for (auto& thread : threads_)
        if (thread.second.joinable())
            thread.second.join();

    threads_.clear();
}

TaskQueue* ThreadPool::getTaskQueue(void) {
    return &tasks_;
}

ThreadPool::Status ThreadPool::status(void) {
    std::lock_guard<std::mutex> lock(statusMutex_);
    return status_;
}

unsigned ThreadPool::threadsPerformingTask(void) const {
    return threadsPerformingTask_;
}

void ThreadPool::loop(void) {
    Task task;
    while (status_ == STATUS_RUNNING) {
        task = Task();

        {
            std::unique_lock<std::mutex> lock(taskMutex_);

            // wait for notification
            taskCV_.wait(lock, [this] { return !tasks_.empty() ||
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

            tasks_.pullTask(task);
        }

        ++threadsPerformingTask_;
        if (task)
            task();
        --threadsPerformingTask_;
    }
}

void ThreadPool::setStatus(ThreadPool::Status status) {
    std::lock_guard<std::mutex> lock(statusMutex_);
    status_ = status;
}
