/**
    Cucca Game Engine - Core - Task.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Task is a function wrapper for ThreadPool to use.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-11-22
**/


#ifndef CUCCA_CORE_TASK_HPP
#define CUCCA_CORE_TASK_HPP


#include <functional>


namespace Cucca {

    class Task {
    public:
        Task(const Task& other);

        //  Constructor for plain function
        Task(void(*f)(void));
        //  Constructor for member function
        template<typename T>
        Task(T* object, void(T::*f)(void));

        void run(void);

    private:
        std::function<void()> f_;
    };


    //  Member definitions
    Task::Task(const Task& other) :
        f_(other.f_)
    {}

    template<typename T>
    Task::Task(T* object, void(T::*f)(void)) :
        f_(std::bind(f, object))
    {}

    Task::Task(void(*f)(void)) :
        f_(std::bind(f))
    {}

    void Task::run(void) {
        f_();
    }

} // namespace Cucca


#endif // CUCCA_CORE_TASK_HPP

