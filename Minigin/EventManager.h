//#pragma once
//#include <memory>
//#include "Singleton.h"
//#include <queue>
//#include "Observer.h"
//#include "BaseEvent.h"
//#include <thread>
//#include <atomic>
//#include <stop_token>
//#include "EventQueue.h"
//#include <list>
//#include <unordered_map>
//#include <forward_list>
//
//#include <typeindex>
//#include <typeinfo>  // for typeid
//#include <type_traits>  // for std::enable_if_t
//#include <IEventListener.h>
//
//
//
//namespace dae
//{
//	class EventManager final : public Singleton<EventManager>
//	{
//	public:
//
//		static void Initialize();
//		static void Shutdown();
//
//		void AddObserver(IObserver* observer, unsigned int eventType);
//		void RemoveObserver(IObserver* observer, unsigned int eventType);
//
//		//template<typename T>
//		//std::enable_if_t<std::is_base_of_v<dae::BaseEvent, T>, T&>
//		//QueueEvent()
//		//{
//		//	return m_EventQueue.RequestSpecificEvent<T>();
//		//}
//		//template <typename SpecificEventType>
//		//SpecificEventType& QueueEvent()
//		//{
//		//	// Get an instance of the event manager and call RequestSpecificEvent to get a HealthEvent
//		//	return GetInstance().m_EventQueue.RequestSpecificEvent<SpecificEventType>();
//		//}
//
//		template<typename T>
//		std::enable_if_t<std::is_base_of_v<dae::BaseEvent, T>, void>
//		AddEvent(std::unique_ptr<T> event)
//		{
//			m_EventQueue.AddEvent(std::move(event));
//		}
//
//	private:
//
//		friend class Singleton<EventManager>;
//		EventManager() = default;
//
//		void StartProcessing();
//		void StopProcessing();
//
//		EventQueue m_EventQueue;
//		std::jthread m_Thread;
//		std::atomic<bool> m_ContinueProcessing = true;
//		std::mutex m_ObserverMutex_;
//
//		typedef std::forward_list<IObserver*> mObserverList;
//		typedef std::unordered_map<unsigned int, mObserverList> 	ObserversMap;
//		ObserversMap m_Observers;
//
//		//template<typename T>
//		//std::enable_if_t<std::is_base_of_v<dae::BaseEvent, T>, void>
//		void NotifyObservers(BaseEvent* event)
//		{
//			std::scoped_lock lock(m_ObserverMutex_);
//
//			auto it = m_Observers.find(event->type);
//			if (it != m_Observers.end())
//			{
//				for (IObserver* observer : it->second)
//				{
//					//auto observerType = typeid(*observer).name();
//					//std::cout << "Notifying observer with type: " << observerType << std::endl;
//
//					//auto observerID = observer->GetID();
//
//					//std::cout << "Notifying observer with ID: " << observerID << std::endl;
//					//auto eventID = event->entityId;
//					//std::cout << "Event ID: " << eventID << std::endl;
//					
//					if (observer->GetID() == event->entityId)
//					{
//						//std::cout << "Notifying observer with ID: " << observer->GetID() << std::endl;
//						
//						
//						observer->OnNotify(event);
//						break; // Break after notifying the targeted observer
//					}
//				}
//			}
//		}
//
//	};
//
//	
//
//}
//
