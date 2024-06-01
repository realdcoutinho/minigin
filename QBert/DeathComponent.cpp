#include "DeathComponent.h"
#include "GameObject.h"
#include <iostream>
#include <TimeManager.h>
#include <Timer.h>
#include "GridNavigator.h"
namespace dae
{
	DeathComponent::DeathComponent(GameObject& pOwner)
		:BaseComponent(pOwner)
	{
		//std::cout << "DeathComponent created" << std::endl;
	}

	void DeathComponent::Render()
	{
	}

	void DeathComponent::Update()
	{
		if (m_IsDead)
		{
			m_CurrentDeathTime += TimeManager::GetInstance().GetTimer().GetElapsed();
			if (m_CurrentDeathTime >= m_DeathTimer)
			{
				GetOwner()->SetActive(false);
				//GetOwner()->SetDestroy();
			}
		}
	}

	void DeathComponent::OnDeath()
	{
		m_IsDead = true;

	}



}

