
#pragma once
#include <string>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <forward_list>
//#include "Event.h"
#include "Observer.h"



namespace dae
{

	class GameObject;
	class ISubject
	{
	public:
		ISubject();
		~ISubject();

		//virtual void AddObserver(IObserver* observer, dae::Event event);
		//virtual void RemoveObserver(IObserver* observer, dae::Event event);

		virtual void NotifyAll(); 
		//virtual void Notify(GameObject* obj, dae::MyEvent event);

	private:
		typedef std::forward_list<IObserver*> mObserverList;
		//typedef std::unordered_map< dae::Event, mObserverList> 	ObserversMap;
		//ObserversMap mObservers;
	};
}
