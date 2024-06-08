#include "EnemyManager.h"
#include "GameInfo.h"
#include "Scene.h"
#include "Timer.h"
#include "GameObjectFactory.h"
#include "CoilyComponent.h"
#include "GameObject.h"
#include "DeathComponent.h"
#include "GridNavigator.h"
#include "CharacterComponent.h"

namespace dae
{
	EnemyManager::EnemyManager()
	{

	}

	EnemyManager::~EnemyManager()
	{

	}

	void EnemyManager::SetNewData(GameInfo& gameInfo)
	{
		m_CanSpawnCoily = gameInfo.spawnCoily;
		m_CanSpawnSlickSam = gameInfo.spawnSam;
		m_CanSpawnUggWrongway = gameInfo.spawnUgg;

		m_CoilyInterval = gameInfo.coilyInterval;
		m_SlickSamInterval = gameInfo.samInterval;
		m_UggWrongwayInterval = gameInfo.uggInterval;

		m_SpawnTimerCoily = 0.f;
		m_SpawnTimerSlickSam = 0.f;
		m_SpawnTimerUggWrongway = 0.f;

		if (gameInfo.gameMode == 3)
			m_VersusMode = true;

		m_pCoily = nullptr;

		m_KeepUpdate = true;
		m_pGameInfo = &gameInfo;
	}

	void EnemyManager::Update()
	{
		if(!m_KeepUpdate)
			return;

		if(!m_pCurrentScene)
			return;
		
		m_pCurrentScene->GetTimer();
		float elapsed = m_pCurrentScene->GetTimer().GetElapsed();

		UpdateCoilySpawnTimers(elapsed);
		UpdateSlickSamSpawnTimers(elapsed);
		UpdateUggWrongwaySpawnTimers(elapsed);
	}



	void EnemyManager::HuntQbert(std::vector<GameObject*> qberts)
	{
		if (m_pCoily == nullptr)
			return;
		auto coilyComp = m_pCoily->GetComponent<CoilyComponent>();
		if (coilyComp == nullptr)
			return;

		coilyComp->Hunt(qberts);
	}

	void EnemyManager::DestroyCoily()
	{
		if (m_pCoily == nullptr)
			return;

		m_pCoily->SetActive(false);
		m_pCoily = nullptr;
		m_CanSpawnCoily = true;
	}

	void EnemyManager::DestroyAllEnemies()
	{
		if (m_pCoily != nullptr)
		{
			m_pCoily->GetComponent<DeathComponent>()->OnDeath();
			m_pCoily->GetComponent<GridNavigator>()->SetDead();
			m_pCoily = nullptr;
		}

		for (auto pEnemy : m_pEnemies)
		{
			pEnemy->GetComponent<GridNavigator>(true)->SetDead();
			pEnemy->GetComponent<DeathComponent>(true)->OnDeath();
		}

		m_pEnemies.clear();
		m_CanSpawnCoily = m_pGameInfo->spawnCoily;
		m_CanSpawnSlickSam = m_pGameInfo->spawnSam;
		m_CanSpawnUggWrongway = m_pGameInfo->spawnUgg;

		m_SpawnTimerCoily = 0;
		m_SpawnTimerSlickSam = 0;
		m_SpawnTimerUggWrongway = 0;

		m_CurrentSlickSam = 0;
		m_CurrentUggWrongway = 0;
	}

	void EnemyManager::DestroyEnemy(GameObject* pEnemy)
	{
		//remove from vector 
		if (pEnemy == nullptr)
			return;

		m_pEnemies.erase(std::remove(m_pEnemies.begin(), m_pEnemies.end(), pEnemy), m_pEnemies.end());

		auto enemyType = pEnemy->GetComponent<CharacterComponent>()->GetType();
		if (enemyType == CharacterType::Slick || enemyType == CharacterType::Sam)
			m_CurrentSlickSam--;
		else if (enemyType == CharacterType::Ugg || enemyType == CharacterType::Wrongway)
			m_CurrentUggWrongway--;
		else if (enemyType == CharacterType::Coily || enemyType == CharacterType::Egg)
			m_pCoily = nullptr;


		pEnemy->GetComponent<DeathComponent>(true)->OnDeath();
		pEnemy->GetComponent<GridNavigator>(true)->SetDead();
	}

	void EnemyManager::Reset()
	{
		DestroyAllEnemies();
		m_KeepUpdate = false;
	}

	void EnemyManager::Restart()
	{
		m_KeepUpdate = true;
	}

	void EnemyManager::UpdateCoilySpawnTimers(float elapsedSec)
	{
		if (m_pCoily != nullptr)
			return;

		if (m_CanSpawnCoily)
		{
			m_SpawnTimerCoily += elapsedSec;
			if (m_SpawnTimerCoily >= m_CoilyInterval)
			{
				m_SpawnTimerCoily = 0;
				SpawnCoily();
			}
		}
	}

	void EnemyManager::UpdateSlickSamSpawnTimers(float elapsedSec)
	{
		if (m_MaxSlickSam <= m_CurrentSlickSam)
		{
			m_CanSpawnSlickSam = false;
		}
		else
		{
			m_CanSpawnSlickSam = true;
		}
		if (m_CanSpawnSlickSam)
		{
			m_SpawnTimerSlickSam += elapsedSec;
			if (m_SpawnTimerSlickSam >= m_SlickSamInterval)
			{
				m_SpawnTimerSlickSam = 0.0f;
				SpawnSlickSam();
			}
		}
	}

	void EnemyManager::UpdateUggWrongwaySpawnTimers(float elapsedSec)
	{
		if (m_CanSpawnUggWrongway)
		{
			if (m_MaxUggWrongway <= m_CurrentUggWrongway)
				return;
			m_SpawnTimerUggWrongway += elapsedSec;
			if (m_SpawnTimerUggWrongway <= m_UggWrongwayInterval)
			{
				m_SpawnTimerUggWrongway = 0.0f;
				SpawnUggWrongway();
			}
		}
	}

	void EnemyManager::SpawnCoily()
	{
		if (!m_VersusMode)
			m_pCoily = &GameObjectFactory::GetInstance().CreateCoily(*m_pCurrentScene, *m_pGrid);
		else
			m_pCoily = &GameObjectFactory::GetInstance().InitializePlayerTwo(*m_pCurrentScene, *m_pGrid, *m_pGameInfo);
	}

	void EnemyManager::SpawnSlickSam()
	{
		auto& enemy = GameObjectFactory::GetInstance().CreateSlickSam(*m_pCurrentScene, *m_pGrid);
		m_pEnemies.push_back(&enemy);
		m_CurrentSlickSam++;
	}

	void EnemyManager::SpawnUggWrongway()
	{
		auto& enemy = GameObjectFactory::GetInstance().CreateUggWrongway(*m_pCurrentScene, *m_pGrid);
		m_pEnemies.push_back(&enemy);
		m_CurrentUggWrongway++;
	}






	//void EnemyManager::MakeCoilyHunt(GridNode& targetNode)
//{
//	if(m_VersusMode)
//		return;

//	if (m_pCoily == nullptr)
//		return;

//	auto coilyComp = m_pCoily->GetComponent<CoilyComponent>();
//	if(coilyComp == nullptr)
//		return;

//	coilyComp->Hunt(targetNode);
//}
}

