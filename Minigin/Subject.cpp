//#include "Subject.h"
//#include "Observer.h"
//
//namespace dae
//{
//	ISubject::ISubject()
//	{
//
//	}
//
//	ISubject::~ISubject() {}
//
//	void ISubject::AddObserver(IObserver* observer, dae::Event event)
//	{
//		auto it = mObservers.find(event);
//		if (it == mObservers.end())
//		{
//			mObservers[event] = mObserverList();
//		}
//
//		mObservers[event].push_front(observer);
//	}
//
//	void ISubject::RemoveObserver(IObserver* observer, dae::Event event)
//	{
//		auto it = mObservers.find(event);
//		if (it == mObservers.end())
//		{
//			mObserverList& list = mObservers[event];
//			for (mObserverList::iterator li = list.begin(); li != list.end();)
//			{
//				if ((*li) == observer)
//				{
//					list.remove(observer);
//				}
//				else
//				{
//					++li;
//				}
//			}
//		}
//	}
//
//
//	void ISubject::NotifyAll()
//	{
//		for (ObserversMap::iterator it = mObservers.begin(); it != mObservers.end(); ++it)
//		{
//			for (auto& o : mObservers[it->first])
//			{
//				o;
//				//o->OnNotify();
//			}
//		}
//	}
//
//	void ISubject::Notify(GameObject* obj, dae::MyEvent event)
//	{
//		obj;
//		event;
//
//		//for (auto& o : mObservers[event])
//		//{
//		//	o;
//		//	
//		//	//o->OnNotify(obj, event);
//		//}
//	}
//}