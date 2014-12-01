/**
    Cucca Game Engine - Core - Task.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Task is a function wrapper for ThreadPool to use.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-01
**/


#ifndef CUCCA_CORE_TASK_HPP
#define CUCCA_CORE_TASK_HPP


#include <functional>


namespace Cucca {

    /*class TaskBase {
    public:
        TaskBase(void) = default;
        TaskBase(const TaskBase&) = default;
        TaskBase(TaskBase&&) = default;
        TaskBase& operator=(const TaskBase&) & = default;
        TaskBase& operator=(TaskBase&&) & = default;

        virtual void operator()(void) const = 0;

        virtual ~TaskBase(void) {}
    };*/

    class Task {
    public:
        Task(const Task& other);

        /// Constructors for plain function
        template <typename... Arguments_T>
        Task(void(*f)(Arguments_T...), Arguments_T... args);

        template <typename... Arguments_T>
        Task(void(*f)(const Arguments_T&...), Arguments_T... args);

        /// Constructors for member function
        template <typename ObjectType_T, typename... Arguments_T>
        Task(ObjectType_T* object, void(ObjectType_T::*f)(Arguments_T...), Arguments_T... args);

        template <typename ObjectType_T, typename... Arguments_T>
        Task(ObjectType_T* object, void(ObjectType_T::*f)(const Arguments_T&...), Arguments_T... args);

        void operator()(void) const;

    private:
        std::function<void(void)> f_;
    };


    /// Member definitions
    Task::Task(const Task& other) :
        f_(other.f_)
    {}

    template <typename... Arguments_T>
    Task::Task(void(*f)(Arguments_T...), Arguments_T... args) :
        f_(std::bind(f, args...))
    {}

    template <typename... Arguments_T>
    Task::Task(void(*f)(const Arguments_T&...), Arguments_T... args) :
        f_(std::bind(f, args...))
    {}

    template <typename ObjectType_T, typename... Arguments_T>
    Task::Task(ObjectType_T* object, void(ObjectType_T::*f)(Arguments_T...), Arguments_T... args) :
        f_(std::bind(f, object, args...))
    {}

    template <typename ObjectType_T, typename... Arguments_T>
    Task::Task(ObjectType_T* object, void(ObjectType_T::*f)(const Arguments_T&...), Arguments_T... args) :
        f_(std::bind(f, object, args...))
    {}

    void Task::operator()(void) const {
        f_();
    }

} // namespace Cucca


#endif // CUCCA_CORE_TASK_HPP

