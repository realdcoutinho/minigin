#pragma once
#include <string>
#include <iostream>
#include "ScoreComponent.h"
#include <vector>
#include "BaseEvent.h"
#include <memory>




namespace dae
{

	class GameObject;
	class IObserver 
	{
		unsigned int observerID;  // Unique identifier for each observer

	public:
		IObserver(unsigned id) : observerID(id) {}

		virtual void OnNotify(BaseEvent* event) = 0;

		unsigned GetID() const { return observerID; }

		// Optional: Equality operator to compare observers based on ID
		bool operator==(const IObserver& other) const {
			return observerID == other.observerID;
		}
	};
}