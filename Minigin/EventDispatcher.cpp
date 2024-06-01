#include "EventDispatcher.h"

void dae::EventDispatcher::Initialize()
{
	//GetInstance().StartEventProcessing();
}

void dae::EventDispatcher::Shutdown()
{
	//GetInstance().StopEventProcessing();
}

void dae::EventDispatcher::StartEventProcessing()
{
	m_Thread = std::jthread([this](std::stop_token stoken)
		{
			while (!stoken.stop_requested())
			{
				auto optionalEvent = m_EventQueue.GetEvent();
				if (optionalEvent && optionalEvent.has_value()) 
				{
					auto& event = optionalEvent.value(); // Reference to the unique_ptr
					if (event) 
					{
						NotifyListeners(event.get());
					}
				}

			}
		});
}

void dae::EventDispatcher::StopEventProcessing()
{
	m_ContinueProcessing.store(false);
	m_Thread.request_stop();  // C++20 way to request thread stop
	m_Thread.join();
}

void dae::EventDispatcher::NotifyListeners(IEvent* event)
{
	//std::scoped_lock lock(m_ObserverMutex_);
	auto it = m_Listeners.find(typeid(*event));
	if (it != m_Listeners.end())
	{
		for (auto& listener : it->second)
		{
			if(listener)
				listener->OnEvent(*event);
		}
	}
}


void dae::EventDispatcher::SubscribeListener(std::shared_ptr<IEventListener> listener)
{
	//std::scoped_lock lock(m_ObserverMutex_);

	auto supportedEvents = listener->GetSupportedEvents();
	for (auto& eventTypeId : supportedEvents)
	{
		m_Listeners[eventTypeId].push_back(listener);
	}
}

void dae::EventDispatcher::DispatchEvent(std::unique_ptr<IEvent> event)
{
	//event;
	m_EventQueue.AddEvent(std::move(event));
}

void dae::EventDispatcher::ProcessEvents()
{
	while (m_ContinueProcessing)

	{
		auto optionalEvent = m_EventQueue.GetEvent();
		if (optionalEvent && optionalEvent.has_value())
		{
			auto& event = optionalEvent.value(); // Reference to the unique_ptr
			if (event)
			{
				NotifyListeners(event.get());
			}
		}
		else
		{
			break; // Break the loop if there are no more events to process
		}

	}
}
