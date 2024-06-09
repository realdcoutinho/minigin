#include "EventQueue.h"

dae::EventQueue::EventQueue() /*: m_Events(m_MaxEvents)*/
{
    for (int j = 0; j < m_MaxEvents; ++j) 
    {
        Events.push_back(std::make_unique<IEvent>());
    }
}

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
