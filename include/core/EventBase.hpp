#ifndef CUCCA_CORE_EVENTBASE_HPP
#define CUCCA_CORE_EVENTBASE_HPP


class EventBase {
public:
    //  Standard constructors/destructors
    EventBase(void);
    virtual ~EventBase(void) {}

    /*  Template constructor
        Constructors cannot be called with template parameters, that's why
        an argument is required for automatic deduction */
    template<typename EventType_T>
    EventBase(EventType_T* event) :
        eventType_(getEventTypeId<EventType_T>())
        {}

    //  Set event. Returns type of the event.
    /*template<typename EventType_T>
    int setEvent(const EventType_T& event) {
        event_ = &event;
        return eventType_ = getEventTypeId<EventType_T>();
    }*/

    //  Get event type. Will return -1 if no event is stored.
    int getEventType(void) const;

    template<typename EventType_T>
    static int getEventTypeId(void) {
        static unsigned numEventTypes__ = 0;
        static int eventTypeId__ = numEventTypes__++;
        return eventTypeId__;
    }

private:

    //  Stored event type identifier
    int eventType_;
};


#endif // CUCCA_CORE_EVENTBASE_HPP
