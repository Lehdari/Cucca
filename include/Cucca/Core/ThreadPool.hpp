/**
    Cucca Game Engine - Core - ThreadPool.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-21
**/


#ifndef CUCCA_CORE_THREADPOOL_HPP
#define CUCCA_CORE_THREADPOOL_HPP


#include <Cucca/Core/TaskQueue.hpp>

#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <unordered_map>
#include <deque>
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

        //  ThreadPool is immovable and incopyable
        ThreadPool(const ThreadPool&) = delete;
        ThreadPool(ThreadPool&&) = delete;

        ThreadPool operator=(const ThreadPool&) = delete;
        ThreadPool operator=(ThreadPool&&) = delete;

        ~ThreadPool(void);

        void launchThreads(unsigned n);
        void joinThreads(unsigned n);

        void terminate(void);

        TaskQueue* getTaskQueue(void);

        Status status(void);
        unsigned threadsPerformingTask(void) const;

    private:
        // loop for worker threads
        void loop(void);

        void setStatus(Status status);

        Status status_;
        std::mutex statusMutex_;

        std::unordered_map<std::thread::id, std::thread> threads_;
        std::atomic_uint threadsToJoin_; // for signaling threads to join
        std::vector<std::thread::id> threadsJoining_; // for joining threads to tell their ids
        std::mutex threadsJoiningMutex_; // for use with condition variable
        std::condition_variable threadsJoiningCV_; // for threads to signal they're joining

        TaskQueue tasks_;
        std::atomic_uint threadsPerformingTask_;
        std::mutex taskMutex_;
        std::condition_variable taskCV_;
    };

} // namespace Cucca


#endif // CUCCA_CORE_THREADPOOL_HPP
