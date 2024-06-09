#include "HealthComponent.h"
#include "Subject.h"
#include "SceneManager.h"
#include "Scene.h"

#include "EventDispatcher.h"
#include <memory.h>
#include "QBertEvents.h"
#include "DeathComponent.h"
#include "GameObject.h"
#include "RespawnComponent.h"
#include "GameModeManager.h"
#include "QBertGameMode.h"
#include "TriangularGrid.h"
#include "QBertComponent.h"



namespace dae
{
	HealthComponent::HealthComponent(GameObject& pOwner, int initialHealht)
		:BaseComponent(pOwner),
		m_Health{ initialHealht }
	{
		auto healthChange = std::make_unique<HealthChangeEventHUD>(GetOwnerID(), m_Health);
		EventDispatcher::GetInstance().DispatchEvent(std::move(healthChange));
	}

	HealthComponent::~HealthComponent()
	{
	}

	void HealthComponent::TakeHit()
	{
		if (m_Health > 0)
		{
			--m_Health;




			//send event to update HUD
			auto healthChange = std::make_unique<HealthChangeEventHUD>(GetOwnerID(), m_Health);
			EventDispatcher::GetInstance().DispatchEvent(std::move(healthChange));

			auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
			auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
			if (qbertGameMode != nullptr)
			{
				qbertGameMode->GetGrid()->UnregisterAllCharacters();
				int playerNumber = GetOwner()->GetComponent<QBertComponent>()->GetPlayerNumber();
				qbertGameMode->SetPlayerLives(m_Health, playerNumber);
			}
		}
	}

	void HealthComponent::Respawn(int idx)
	{
		if (m_Health > 0)
		{
			GetOwner()->GetComponent<RespawnComponent>()->OnRespawn(idx);
		}
		else
		{
			auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
			auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
			if (qbertGameMode != nullptr)
			{
				qbertGameMode->PlayerDied();
			}
		}
	}

	int HealthComponent::GetHealth() const
	{
		return m_Health;
	}

	void HealthComponent::Update()
	{

	}

	void HealthComponent::Render()
	{
	}
}
