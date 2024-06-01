//#include "EventManager.h"
//#include "BaseEvent.h"
//#include "Observer.h"
//
//
//void dae::EventManager::Initialize()
//{
//
//	GetInstance().StartProcessing();
//}
//
//void dae::EventManager::Shutdown()
//{
//	GetInstance().StopProcessing();
//}
//
//
//
//void dae::EventManager::AddObserver(IObserver* observer, unsigned int eventType)
//{
//	std::scoped_lock lock(m_ObserverMutex_);
//	auto it = m_Observers.find(eventType);
//	if (it == m_Observers.end())
//	{
//		m_Observers[eventType] = mObserverList();
//	}
//
//	m_Observers[eventType].push_front(observer);
//}
//
//void dae::EventManager::RemoveObserver(IObserver* observer, unsigned int eventType)
//{
//	std::scoped_lock lock(m_ObserverMutex_);
//	//m_Observers.remove(observer);
//
//	auto it = m_Observers.find(eventType);
//	if (it == m_Observers.end())
//	{
//		mObserverList& list = m_Observers[eventType];
//		for (mObserverList::iterator li = list.begin(); li != list.end();)
//		{
//			if ((*li) == observer)
//			{
//				list.remove(observer);
//			}
//			else
//			{
//				++li;
//			}
//		}
//	}
//}
//
////void dae::EventManager::NotifyObservers(BaseEvent* event)
////{
////	std::scoped_lock lock(m_ObserverMutex_);
////
////	auto it = m_Observers.find(event->type);
////	if (it != m_Observers.end()) 
////	{
////		for (IObserver* observer : it->second)
////		{
////			if (observer->GetID() == event->entityId)
////			{
////				std::cout << "Notifying observer with ID: " << observer->GetID() << std::endl;
////				observer->OnNotify(event);
////				break; // Break after notifying the targeted observer
////			}
////		}
////	}
////
////}
//
//void dae::EventManager::StartProcessing()
//{
//	
//	m_Thread = std::jthread([this](std::stop_token stoken)
//	{
//		while (!stoken.stop_requested())
//		{
//			auto eventOpt = m_EventQueue.DequeueEvent();
//			if (eventOpt.has_value())
//			{
//
//				//Notify the event, e.g., dispatch to listeners
//				if(eventOpt.value().get()) //idk why this is needed, but it is
//					NotifyObservers(eventOpt.value().get());
//	
//			}
//		}
//	});
//}
//
//
//
//
//
//void dae::EventManager::StopProcessing()
//{
//	m_ContinueProcessing.store(false);
//	m_Thread.request_stop();  // C++20 way to request thread stop
//	m_Thread.join();
//}
//
//
//
//
//
//
//
//
//
