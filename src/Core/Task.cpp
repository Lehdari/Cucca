/**
    Cucca Game Engine - Core - Task.cpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-21
**/


#include "../../include/Core/Task.hpp"


using namespace Cucca;


Task::Task(void) :
    f_(nullptr),
    flag_(FLAG_DEFAULT)
{}

/*Task::Task(const Task& other) :
    f_(other.f_),
    flag_(other.flag_)
{}

Task::Task(Task&& other) :
    f_(std::move(other.f_)),
    flag_(std::move(other.flag_))
{}

Task& Task::operator=(const Task& other) {
    f_ = other.f_;
    flag_ = other.flag_;
    return *this;
}

Task& Task::operator=(Task&& other) {
    f_ = std::move(other.f_);
    flag_ = std::move(other.flag_);
    other.f_ = nullptr;
    return *this;
}*/


void Task::operator()(void) const {
    f_();
}

Task::operator bool() const {
    if (f_)
        return true;
    else
        return false;
}
