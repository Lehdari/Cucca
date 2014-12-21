/**
    Cucca Game Engine - Core - TaskQueue.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-21
**/


#include "../../include/Core/ThreadPool.hpp"


#include <algorithm>


using namespace Cucca;


TaskQueue::TaskQueue(std::condition_variable* CV) :
    CV_(CV)
{}

void TaskQueue::pushTask(const Task& task) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.push_back(task);
    if (CV_)
        CV_->notify_all();
}

void TaskQueue::pushTask(Task&& task) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.push_back(task);
    if (CV_)
        CV_->notify_all();
}

bool TaskQueue::pullTask(Task& task) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (!tasks_.empty()) {
        task = std::move(tasks_.front());
        tasks_.pop_front();
        return true;
    }
    else
        return false;
}

void TaskQueue::removeTasks(Task::Flag flag) {
    std::lock_guard<std::mutex> lock(mutex_);
    tasks_.erase(std::remove_if(tasks_.begin(), tasks_.end(), [flag](Task& task) { return task.flag_ == flag; }), tasks_.end());
}

bool TaskQueue::empty(void) {
    std::lock_guard<std::mutex> lock(mutex_);
    return tasks_.empty();
}
