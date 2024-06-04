#include "HealthComponent.h"
#include "Subject.h"
#include "SceneManager.h"
#include "Scene.h"
#include "EventManager.h"
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
				qbertGameMode->GameOver();
				//qbertGameMode->GetGrid()->UnregisterAllCharacters();
				//int playerNumber = GetOwner()->GetComponent<QBertComponent>()->GetPlayerNumber();
				//qbertGameMode->SetPlayerLives(m_Health, playerNumber);
			}

			//GetOwner()->GetComponent<DeathComponent>()->OnDeath();
			//auto allEnemiesDeath = std::make_unique<EraseAllEnemiesEvent>(GetOwnerID());
			//EventDispatcher::GetInstance().DispatchEvent(std::move(allEnemiesDeath));


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
