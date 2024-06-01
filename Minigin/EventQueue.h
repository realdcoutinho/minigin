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

		//BaseEvent& RequestEvent();

        //template <typename SpecificEventType>
        //SpecificEventType& RequestSpecificEvent() 
        //{
        //    std::scoped_lock lock(m_Mutex);
        //    if ((m_Tail + 1) % m_MaxEvents == m_Head) {
        //        // Increment head if buffer is full
        //        m_Head = (m_Head + 1) % m_MaxEvents;
        //    }

        //    // Create a new event if the existing one is not of the right type
        //    if (!std::dynamic_pointer_cast<SpecificEventType>(m_Events[m_Tail])) {
        //        m_Events[m_Tail] = std::make_shared<SpecificEventType>();
        //    }

        //    auto& event = m_Events[m_Tail];
        //    m_Tail = (m_Tail + 1) % m_MaxEvents;
        //    return *std::static_pointer_cast<SpecificEventType>(event);

        //}


        //std::optional<std::unique_ptr<dae::BaseEvent>> DequeueEvent();

        std::optional<std::unique_ptr<dae::IEvent>> GetEvent();

        //template<typename T>
        //std::enable_if_t<std::is_base_of_v<dae::BaseEvent, T>, void>
        //    AddEvent(std::unique_ptr<T> event)
        //{
        //    std::scoped_lock lock(m_Mutex);
        //    if ((m_Tail + 1) % m_MaxEvents == m_Head) {
        //        // Increment head if buffer is full
        //        m_Head = (m_Head + 1) % m_MaxEvents;
        //    }
        //    m_Events[m_Tail] = std::move(event);
        //    m_Tail = (m_Tail + 1) % m_MaxEvents;
        //}
        
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
        //std::vector<std::unique_ptr<dae::BaseEvent>> m_Events;

        std::vector<std::unique_ptr<dae::IEvent>> Events;

        int head = 0;
        int tail = 0;

        int m_Head = 0;
		int m_Tail = 0;
		static constexpr int m_MaxEvents = 30;
		std::mutex m_Mutex;

	};
}