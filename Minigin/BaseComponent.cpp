#include "BaseComponent.h"
#include "GameObject.h" // Include GameObject here


namespace dae
{
	unsigned int BaseComponent::m_idCounter = 0;

	unsigned int BaseComponent::GetOwnerID() const
	{
		return GetOwner()->GetID();
	}

	BaseComponent::BaseComponent(std::unique_ptr<GameObject> pOwner)
		: m_ComponentId(0)
	{
		SetOwner(pOwner.get());
		++m_idCounter;
		m_ComponentId = m_idCounter;
	}
	BaseComponent::BaseComponent(GameObject& pOwner) 
		: m_ComponentId(0)
	{
		SetOwner(&pOwner);
		++m_idCounter;
		m_ComponentId = m_idCounter;
	}

	void BaseComponent::SetOwner(GameObject* pOwner)
	{
		if (!pOwner)
			return;
		m_pOwner = pOwner;
	}
}