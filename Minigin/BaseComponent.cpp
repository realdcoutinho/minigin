#include "BaseComponent.h"
#include "GameObject.h" // Include GameObject here


namespace dae
{
	unsigned int BaseComponent::m_idCounter = 0;

	BaseComponent::BaseComponent(std::shared_ptr<GameObject> pOwner) : /*m_pOwner(pOwner),*/ m_pScene(nullptr), m_IsInitialized(false), m_ComponentId(0)
	{
		SetOwner(pOwner.get());


		++m_idCounter;
		m_ComponentId = m_idCounter;
		m_IsInitialized = true;
	}
	BaseComponent::BaseComponent(GameObject* pOwner) : /*m_pOwner(pOwner),*/ m_pScene(nullptr), m_IsInitialized(false), m_ComponentId(0)
	{
		SetOwner(pOwner);
	}

	void BaseComponent::SetOwner(GameObject* pOwner)
	{
		if (!pOwner)
			return;
		m_pOwner = pOwner;
	}
}