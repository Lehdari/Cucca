/**
    Cucca Game Engine - Core - TaskQueue.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-21
**/


#ifndef CUCCA_CORE_TASKQUEUE_HPP
#define CUCCA_CORE_TASKQUEUE_HPP


#include <Cucca/Core/Task.hpp>

#include <deque>
#include <mutex>
#include <condition_variable>


namespace Cucca {

    class TaskQueue {
    public:
        TaskQueue(std::condition_variable* CV = nullptr);

        void pushTask(const Task& task);
        void pushTask(Task&& task);

        bool pullTask(Task& task);

        void removeTasks(Task::Flag flag);

        bool empty(void);

    private:
        std::deque<Task> tasks_;
        std::mutex mutex_;
        std::condition_variable* CV_;
    };

} // namespace Cucca


#endif // CUCCA_CORE_TASKQUEUE_HPP
