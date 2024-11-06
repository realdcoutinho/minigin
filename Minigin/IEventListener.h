#pragma once
#include <typeinfo>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "BaseEvent.h"

// Event Listener Interface
namespace dae
{
    class BaseEvent;
    class IEventListener
    {
    public:
        virtual ~IEventListener() = default;
        virtual void OnEvent(IEvent& event) = 0;
        virtual std::vector<std::type_index> GetSupportedEvents() = 0;
    };
}
