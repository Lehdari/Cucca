/**
    Cucca Game Engine - Core - Device.hpp

    This file is subject to the terms and conditions defined in
    file 'LICENSE.txt', which is part of this source code package.

    @version    0.1
    @author     Miika Lehtimäki
    @date       2015-01-10
**/


#ifndef CUCCA_CORE_DEVICE_HPP
#define CUCCA_CORE_DEVICE_HPP


#include <Cucca/Core/Node.hpp>
#include <Cucca/Core/Canvas.hpp>
#include <Cucca/Core/Event.hpp>
#include <Cucca/Core/EventComponent.hpp>
#include <Cucca/Core/TaskQueue.hpp>

#include <deque>
#include <unordered_map>
#include <vector>
#include <memory>
#include <mutex>
#include <GL/glew.h>


#define DEVICE(CANVAS_TYPE) Device<CANVAS_TYPE>::getInstance()


namespace Cucca {

    template<typename CanvasType_T>
    class Device {
    public:
        enum Status {
            STATUS_RUNNING,
            STATUS_TERMINATED
        };

        //  Device is immovable and incopyable
        Device<CanvasType_T>(const Device<CanvasType_T>&) = delete;
        Device<CanvasType_T>(Device<CanvasType_T>&&) = delete;

        Device<CanvasType_T>& operator=(const Device<CanvasType_T>&) = delete;
        Device<CanvasType_T>& operator=(Device<CanvasType_T>&&) = delete;

        //  Get singleton instance
        static Device<CanvasType_T>* getInstance(void);

        //  Renders and performs graphics tasks
        void render(void);

        //  Polls the canvas events and empties pushed events
        void handleEvents(void);

        //  Get status
        Status status(void);

        //  Terminate the device (shut down the application)
        void terminate(void);

        //  Get pointer to root node
        Node* getRoot(void);

        //  Push an event into event queue
        void pushEvent(EventBase& event);
        void pushEvent(EventBase&& event);

        //  Subscribe events of specific type (use EventBase::getEventTypeId for correct id)
        void subscribeEvents(EventComponent* eventComponent, int eventTypeId);

        //
        CanvasType_T* getCanvas(void); // TODO: const pointer?

        //
        TaskQueue* getGraphicsTaskQueue(void); // TODO: const pointer?

    private:
        //  Singleton pattern
        static std::unique_ptr<Device<CanvasType_T>> instance__;
        Device(void);

        static std::mutex instanceMutex__;

        Status status_;
        std::unique_ptr<Node> root_;
        std::mutex quickAccessMutex_; // for getters/setters mainly

        CanvasType_T canvas_;
        std::mutex canvasMutex_;

        //  Event queue
        std::deque<std::shared_ptr<EventBase>> events_;
        //  Event type id mapping for subscribers
        std::unordered_map<int, std::vector<EventComponent*>> eventSubscribers_;
        std::mutex eventMutex_;

        //  Graphics task queue
        TaskQueue graphicsTasks_;
    };


    //  Member definitions
    template<typename CanvasType_T>
    std::unique_ptr<Device<CanvasType_T>> Device<CanvasType_T>::instance__ = std::unique_ptr<Device<CanvasType_T>>(nullptr);

    template<typename CanvasType_T>
    std::mutex Device<CanvasType_T>::instanceMutex__;


    template<typename CanvasType_T>
    Device<CanvasType_T>::Device(void) :
        status_(STATUS_RUNNING),
        root_(std::unique_ptr<Node>(new Node()))
    {
        glEnable(GL_DEPTH_TEST);
    }

    template<typename CanvasType_T>
    Device<CanvasType_T>* Device<CanvasType_T>::getInstance(void) {
        std::lock_guard<std::mutex> lock(instanceMutex__);
        if (!instance__)
            instance__ = std::unique_ptr<Device<CanvasType_T>>(new Device<CanvasType_T>());
        return instance__.get();
    }

    template<typename CanvasType_T>
    void Device<CanvasType_T>::render(void) {
        {
            std::lock_guard<std::mutex> lock(canvasMutex_);
            if (canvas_.isOpen()) {
                canvas_.display();
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }
        }

        Task task;
        while (true) {
            if (graphicsTasks_.empty())
                return;

            if (graphicsTasks_.pullTask(task))
                task();

            //  TODO_IMPLEMENT: chrono timer so that fps won't drop when there is too much tasks in the queue
        }
    }

    template<typename CanvasType_T>
    void Device<CanvasType_T>::handleEvents(void) {
        std::lock_guard<std::mutex> lock(eventMutex_);
        std::shared_ptr<EventBase> event;

        //  first poll events from canvas
        {
            std::lock_guard<std::mutex> lock(canvasMutex_);
            event = canvas_.pollEvent();

            while (event) {
                int eventType = event.get()->getEventType(); // TODO? invalid type check?
                for (auto& eventComponent : eventSubscribers_[eventType])
                    eventComponent->pushEvent(event);

                event = canvas_.pollEvent();
            }
        }

        //  then empty the event queue
        if (events_.empty())
            return;
        event = events_.front();
        events_.pop_front();

        while (event) {
            int eventType = event.get()->getEventType();
            for (auto& eventComponent : eventSubscribers_[eventType])
                eventComponent->pushEvent(event);

            if (events_.empty())
                return;
            event = events_.front();
            events_.pop_front();
        }
    }

    template<typename CanvasType_T>
    typename Device<CanvasType_T>::Status Device<CanvasType_T>::status(void) {
        std::lock_guard<std::mutex> lock(quickAccessMutex_);
        return status_;
    }

    template<typename CanvasType_T>
    void Device<CanvasType_T>::terminate(void) {
        canvas_.close();

        std::lock_guard<std::mutex> lock(quickAccessMutex_);
        status_ = STATUS_TERMINATED;
    }

    template<typename CanvasType_T>
    Node* Device<CanvasType_T>::getRoot(void) {
        std::lock_guard<std::mutex> lock(quickAccessMutex_);
        return root_.get();
    }

    template<typename CanvasType_T>
    void Device<CanvasType_T>::pushEvent(EventBase& event) {
        std::lock_guard<std::mutex> lock(eventMutex_);
        events_.push_back(std::make_shared<EventBase>(event));
    }

    template<typename CanvasType_T>
    void Device<CanvasType_T>::subscribeEvents(EventComponent* eventComponent, int eventTypeId) {
        std::lock_guard<std::mutex> lock(eventMutex_);
        eventSubscribers_[eventTypeId].push_back(eventComponent);
    }

    template<typename CanvasType_T>
    CanvasType_T* Device<CanvasType_T>::getCanvas(void) {
        return &canvas_;
    }

    template<typename CanvasType_T>
    TaskQueue* Device<CanvasType_T>::getGraphicsTaskQueue(void) {
        return &graphicsTasks_;
    }
} // namespace Cucca


#endif // CUCCA_CORE_DEVICE_HPP
