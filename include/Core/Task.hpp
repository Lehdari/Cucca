/**
    Cucca Game Engine - Core - Task.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    Task is a function wrapper for ThreadPool to use.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2014-12-06
**/


#ifndef CUCCA_CORE_TASK_HPP
#define CUCCA_CORE_TASK_HPP


#include <functional>


namespace Cucca {

    class Task {
    public:
        enum Flag { //  flags for identification
            FLAG_DEFAULT,
            //  tasks created by a ResourceManager, used to remove tasks
            //  from the queue when ResourceManager is destroying
            FLAG_RESOURCEMANAGER
        };

        friend class ThreadPool;

        Task(const Task& other);

        /// Constructors for plain function
        template <typename... Arguments_T>
        Task(void(*f)(Arguments_T...), Arguments_T... args);
        template <typename... Arguments_T>
        Task(void(*f)(const Arguments_T&...), Arguments_T... args);

        template <typename... Arguments_T>
        Task(Flag flag, void(*f)(Arguments_T...), Arguments_T... args);
        template <typename... Arguments_T>
        Task(Flag flag, void(*f)(const Arguments_T&...), Arguments_T... args);

        /// Constructors for member function
        template <typename ObjectType_T, typename... Arguments_T>
        Task(ObjectType_T* object, void(ObjectType_T::*f)(Arguments_T...), Arguments_T... args);
        template <typename ObjectType_T, typename... Arguments_T>
        Task(ObjectType_T* object, void(ObjectType_T::*f)(const Arguments_T&...), Arguments_T... args);

        template <typename ObjectType_T, typename... Arguments_T>
        Task(Flag flag, ObjectType_T* object, void(ObjectType_T::*f)(Arguments_T...), Arguments_T... args);
        template <typename ObjectType_T, typename... Arguments_T>
        Task(Flag flag, ObjectType_T* object, void(ObjectType_T::*f)(const Arguments_T&...), Arguments_T... args);

        /// Constructors for std::function
        template <typename... Arguments_T>
        Task(const std::function<void(Arguments_T...)>& f, Arguments_T... args);
        template <typename... Arguments_T>
        Task(const std::function<void(const Arguments_T&...)>& f, const Arguments_T&... args);

        template <typename... Arguments_T>
        Task(Flag flag, const std::function<void(Arguments_T...)>& f, Arguments_T... args);
        template <typename... Arguments_T>
        Task(Flag flag, const std::function<void(const Arguments_T&...)>& f, const Arguments_T&... args);

        void operator()(void) const;

    private:
        std::function<void(void)> f_;

        Flag flag_;
    };


    /// Member definitions
    Task::Task(const Task& other) :
        f_(other.f_),
        flag_(other.flag_)
    {}

    template <typename... Arguments_T>
    Task::Task(void(*f)(Arguments_T...), Arguments_T... args) :
        f_(std::bind(f, args...)),
        flag_(FLAG_DEFAULT)
    {}

    template <typename... Arguments_T>
    Task::Task(void(*f)(const Arguments_T&...), Arguments_T... args) :
        f_(std::bind(f, args...)),
        flag_(FLAG_DEFAULT)
    {}

    template <typename... Arguments_T>
    Task::Task(Flag flag, void(*f)(Arguments_T...), Arguments_T... args) :
        f_(std::bind(f, args...)),
        flag_(flag)
    {}

    template <typename... Arguments_T>
    Task::Task(Flag flag, void(*f)(const Arguments_T&...), Arguments_T... args) :
        f_(std::bind(f, args...)),
        flag_(flag)
    {}

    template <typename ObjectType_T, typename... Arguments_T>
    Task::Task(ObjectType_T* object, void(ObjectType_T::*f)(Arguments_T...), Arguments_T... args) :
        f_(std::bind(f, object, args...)),
        flag_(FLAG_DEFAULT)
    {}

    template <typename ObjectType_T, typename... Arguments_T>
    Task::Task(ObjectType_T* object, void(ObjectType_T::*f)(const Arguments_T&...), Arguments_T... args) :
        f_(std::bind(f, object, args...)),
        flag_(FLAG_DEFAULT)
    {}

    template <typename ObjectType_T, typename... Arguments_T>
    Task::Task(Flag flag, ObjectType_T* object, void(ObjectType_T::*f)(Arguments_T...), Arguments_T... args) :
        f_(std::bind(f, object, args...)),
        flag_(flag)
    {}

    template <typename ObjectType_T, typename... Arguments_T>
    Task::Task(Flag flag, ObjectType_T* object, void(ObjectType_T::*f)(const Arguments_T&...), Arguments_T... args) :
        f_(std::bind(f, object, args...)),
        flag_(flag)
    {}

    template <typename... Arguments_T>
    Task::Task(const std::function<void(Arguments_T...)>& f, Arguments_T... args) :
        f_(std::bind(f, args...)),
        flag_(FLAG_DEFAULT)
    {}

    template <typename... Arguments_T>
    Task::Task(const std::function<void(const Arguments_T&...)>& f, const Arguments_T&... args) :
        f_(std::bind(f, args...)),
        flag_(FLAG_DEFAULT)
    {}

    template <typename... Arguments_T>
    Task::Task(Flag flag, const std::function<void(Arguments_T...)>& f, Arguments_T... args) :
        f_(std::bind(f, args...)),
        flag_(flag)
    {}

    template <typename... Arguments_T>
    Task::Task(Flag flag, const std::function<void(const Arguments_T&...)>& f, const Arguments_T&... args) :
        f_(std::bind(f, args...)),
        flag_(flag)
    {}

    void Task::operator()(void) const {
        f_();
    }

} // namespace Cucca


#endif // CUCCA_CORE_TASK_HPP

