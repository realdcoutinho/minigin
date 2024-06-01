#include "EventQueue.h"

dae::EventQueue::EventQueue() /*: m_Events(m_MaxEvents)*/
{
    for (int j = 0; j < m_MaxEvents; ++j) 
    {
        Events.push_back(std::make_unique<IEvent>());
    }
    // Initialize all events in the queue
 //   for (int i = 0; i < m_MaxEvents; ++i) 
 //   {
	//	m_Events[i] = std::make_unique<BaseEvent>();
	//}



}

//dae::BaseEvent& dae::EventQueue::RequestEvent()
//{
//    std::scoped_lock lock(m_Mutex);
//    if ((m_Tail + 1) % m_MaxEvents == m_Head) {
//        // If buffer is full, overwrite oldest event (or expand buffer, depending on design choice)
//        m_Head = (m_Head + 1) % m_MaxEvents;  // Move head forward to make room
//    }
//    auto& event = m_Events[m_Tail];
//    m_Tail = (m_Tail + 1) % m_MaxEvents;
//    return *event.get();
//}

std::optional<std::unique_ptr<dae::IEvent>> dae::EventQueue::GetEvent()
{
    std::scoped_lock lock(m_Mutex);
    if (head == tail)
    {
	    return std::nullopt;  // No events to process
	}
	auto event = std::move(Events[head]);  // Move the unique_ptr out of the container
	Events[head].reset(); // Ensure the moved-from slot is reset (optional but clean)
    head = (head + 1) % m_MaxEvents;
	return std::move(event);  // Return the moved unique_ptr
}



//std::optional<std::unique_ptr<dae::BaseEvent>> dae::EventQueue::DequeueEvent()
//{
//    return std::nullopt;
//
//    //std::scoped_lock lock(m_Mutex);
//    //if (m_Head == m_Tail)
//    //{
//    //    return std::nullopt;  // No events to process
//    //}
//    //auto event = std::move(m_Events[m_Head]);  // Move the unique_ptr out of the container
//    //m_Head = (m_Head + 1) % m_MaxEvents;
//    //m_Events[m_Head].reset(); // Ensure the moved-from slot is reset (optional but clean)
//    //return std::move(event);  // Return the moved unique_ptr
//}

//void dae::EventQueue::AddEvent(std::unique_ptr<dae::BaseEvent> event)
//{
//	std::scoped_lock lock(m_Mutex);
//    if ((m_Tail + 1) % m_MaxEvents == m_Head) {
//		// Increment head if buffer is full
//		m_Head = (m_Head + 1) % m_MaxEvents;
//	}
//	m_Events2[m_Tail] = std::move(event);
//	m_Tail = (m_Tail + 1) % m_MaxEvents;
//}