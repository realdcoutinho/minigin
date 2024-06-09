#pragma once

namespace dae 
{
    class GameObject;

    using eventType = unsigned int;
    class BaseEvent
    {
        public:
             BaseEvent() = default;
             BaseEvent(unsigned int id, GameObject* origin, eventType typeEventId)
                : entityId(id), sender(origin), type(typeEventId) {}
            GameObject* sender;
            unsigned int entityId;
            eventType type;

            virtual ~BaseEvent() {}  // Virtual destructor
    };


    class IEvent {
    public:
        IEvent() = default;
        virtual ~IEvent() = default;
    };
}