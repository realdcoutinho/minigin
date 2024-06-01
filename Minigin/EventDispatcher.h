#pragma once
#pragma once
#include <memory>
#include "Singleton.h"
#include <queue>
#include "Observer.h"
#include "BaseEvent.h"
#include <thread>
#include <atomic>
#include <stop_token>
#include "EventQueue.h"
#include <list>
#include <unordered_map>
#include <forward_list>

#include <typeindex>
#include <typeinfo>  // for typeid
#include <type_traits>  // for std::enable_if_t
#include <IEventListener.h>


namespace dae
{
	class EventDispatcher final : public Singleton<EventDispatcher>
	{
	public:
		static void Initialize();
		static void Shutdown();

		void SubscribeListener(std::shared_ptr<IEventListener> listener);
		void DispatchEvent(std::unique_ptr<IEvent> event);

		void ProcessEvents();

	private:
		friend class Singleton<EventDispatcher>;
		EventDispatcher() = default;

		std::unordered_map<std::type_index, std::vector<std::shared_ptr<IEventListener>>> m_Listeners;


		EventQueue m_EventQueue;
		std::jthread m_Thread;
		std::atomic<bool> m_ContinueProcessing = true;
		std::mutex m_ObserverMutex_;

		void StartEventProcessing();
		void StopEventProcessing();


		void NotifyListeners(IEvent* event);
	};
}