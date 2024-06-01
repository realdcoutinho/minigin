//#include "ScoreComponent.h"
//#include "Subject.h"
//#include "EventManager.h"
//#include "GameObject.h"
//#include "Event.h"
//#include "EventManager.h"
//#include <memory>
//
//namespace dae 
//{
//	ScoreComponent::ScoreComponent(GameObject& pOwner, int intialPoints)
//		:BaseComponent(pOwner),
//		m_Score{ intialPoints }
//	{
//	}
//
//	ScoreComponent::~ScoreComponent()
//	{
//
//	}
//
//	void ScoreComponent::SetScore(int score)
//	{
//		m_Score += score;
//		auto eventRef = std::make_unique<TemplateEvent<int>>(GetOwner()->GetID(), GetOwner(), EventType::ScoreChange, m_Score);
//		EventManager::GetInstance().AddEvent(std::move(eventRef));
//	}
//
//	int ScoreComponent::GetScore() const
//	{
//		return m_Score;
//
//	}
//
//	void ScoreComponent::Update()
//	{
//
//	}
//
//	void ScoreComponent::Render()
//	{
//
//	}
//}
