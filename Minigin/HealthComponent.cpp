//#include "HealthComponent.h"
//#include "Subject.h"
//#include "SceneManager.h"
//#include "Scene.h"
//#include "EventManager.h"
//#include <memory.h>
//
//namespace dae
//{
//	HealthComponent::HealthComponent(GameObject& pOwner, int initialHealht)
//		:BaseComponent(pOwner),
//		m_Health{ initialHealht }
//	{
//	}
//
//	HealthComponent::~HealthComponent()
//	{
//	}
//
//	void HealthComponent::SetHealth(int health)
//	{
//		if (m_Health > 0)
//		{
//			m_Health += health;
//			auto eventRef = std::make_unique<TemplateEvent<int>>(GetOwner()->GetID(), GetOwner(), EventType::HealthChange, m_Health);
//			EventManager::GetInstance().AddEvent(std::move(eventRef));
//		}
//		if (m_Health <= 0)
//		{
//			GetOwner()->SetActive(false);
//		}
//	}
//
//	int HealthComponent::GetHealth() const
//	{
//		return m_Health;
//	}
//
//	void HealthComponent::Update()
//	{
//
//	}
//
//	void HealthComponent::Render()
//	{
//	}
//}
