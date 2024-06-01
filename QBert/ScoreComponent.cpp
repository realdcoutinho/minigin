#include "ScoreComponent.h"
#include "ScoreComponent.h"
#include "Subject.h"
#include "EventManager.h"
#include "GameObject.h"
#include "BaseEvent.h"
#include "EventManager.h"
#include <memory>
#include "QbertEvents.h"
#include "EventDispatcher.h"


namespace dae
{
	ScoreComponent::ScoreComponent(GameObject& pOwner, int intialPoints)
		:BaseComponent(pOwner),
		m_Score{ intialPoints }
	{
	}

	ScoreComponent::~ScoreComponent()
	{

	}

	void ScoreComponent::SetScore(int score)
	{
		m_Score += score;
		//auto id = GetOwner()->GetID();
		//auto eventRef = std::make_unique<TemplateEvent<int>>(id, GetOwner(), EventType::ScoreChange, m_Score);
		//EventManager::GetInstance().AddEvent(std::move(eventRef));


		//std::unique_ptr<IEvent> event1 = std::make_unique<PlayerScoredEvent>(m_Score, GetOwnerID());  // Event for player 1
		//EventDispatcher::GetInstance().QueueEvent(std::move(event1));
	}

	int ScoreComponent::GetScore() const
	{
		return m_Score;

	}

	void ScoreComponent::Update()
	{

	}

	void ScoreComponent::Render()
	{

	}
}
