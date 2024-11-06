#include <vector>
#include <mutex>
#include <condition_variable>
#include <optional>
#include "BaseEvent.h"
#include <memory>
#include <typeindex>
#include <typeinfo>  // for typeid
#include <type_traits>  // for std::enable_if_t


#pragma once
namespace dae
{ 
	class EventQueue
	{
	public:
		EventQueue();

        std::optional<std::unique_ptr<dae::IEvent>> GetEvent();

        void AddEvent(std::unique_ptr<IEvent> event)
        {
            std::scoped_lock lock(m_Mutex);
            if ((tail + 1) % m_MaxEvents == head) {
                // Increment head if buffer is full
                head = (head + 1) % m_MaxEvents;
            }
            Events[tail] = std::move(event);
            tail = (tail + 1) % m_MaxEvents;
        }



	private:

        std::vector<std::unique_ptr<dae::IEvent>> Events;

        int head = 0;
        int tail = 0;

        int m_Head = 0;
		int m_Tail = 0;
		static constexpr int m_MaxEvents = 30;
		std::mutex m_Mutex;

	};
}