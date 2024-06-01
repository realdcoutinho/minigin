#include "RespawnComponent.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "Timer.h"
#include "GridNavigator.h"
#include "EnemyManager.h"
#include "GameModeManager.h"
#include "QBertGameMode.h"
#include "EventDispatcher.h"
#include "QBertEvents.h"
#include "TriangularGrid.h"
#include "TextureComponent.h"


namespace dae
{
	RespawnComponent::RespawnComponent(GameObject& pOwner)
		:BaseComponent(pOwner), m_IsRespawning{ false }, m_RespawnTimer{ 2.0f }, m_CurrentRespawnTime{ 0.0f }
	{
	}
	
	void RespawnComponent::Render()
	{
	}

	void RespawnComponent::Update()
	{
		if (m_IsRespawning)
		{
			m_CurrentRespawnTime += TimeManager::GetInstance().GetTimer().GetElapsed();
			
			if (m_CurrentRespawnTime >= m_RespawnTimer / 2.0f)
			{
				if (!m_DoOnde)
				{
					m_DoOnde = true;
					auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
					auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
					if (qbertGameMode != nullptr)
					{
						qbertGameMode->CanBertRender(false);
					}

				}

			}
			if (m_CurrentRespawnTime >= m_RespawnTimer)
			{
				m_IsRespawning = false;
				m_DoOnde = false;
				auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
				auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
				if (qbertGameMode != nullptr)
				{
					qbertGameMode->CanBertRender(true);
				}

				GetOwner()->GetComponent<GridNavigator>()->SetAlive();
				GetOwner()->GetComponent<GridNavigator>()->SetNewPostion(m_RespawnIndex);

			}

		}
	}

	void RespawnComponent::OnRespawn(int idx)
	{
		m_IsRespawning = true;
		m_CurrentRespawnTime = 0.0f;
		m_RespawnIndex = idx;
		GetOwner()->GetComponent<GridNavigator>()->SetDead();
		
		auto allEnemiesDeath = std::make_unique<EraseAllEnemiesEvent>(GetOwnerID());
		EventDispatcher::GetInstance().DispatchEvent(std::move(allEnemiesDeath));

		auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
		auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
		if (qbertGameMode != nullptr)
		{
			qbertGameMode->GetGrid()->UnregisterAllCharacters();
		}
	}


}

