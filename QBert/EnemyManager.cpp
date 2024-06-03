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
		m_SpawnCoily = gameInfo.spawnCoily;
		m_SpawnSlickSam = gameInfo.spawnSam;
		m_SpawnUggWrongway = gameInfo.spawnUgg;

		//m_MaxCoily = gameInfo.maxCoily;
		//m_MaxSlickSam = gameInfo.maxSam;
		//m_MaxUggWrongway = gameInfo.maxUgg;

		m_CoilyInterval = gameInfo.coilyInterval;
		m_SlickSamInterval = gameInfo.samInterval;
		m_UggWrongwayInterval = gameInfo.uggInterval;

		m_SpawnTimerCoily = m_CoilyInterval;
		m_SpawnTimerSlickSam = 5.0f;
		m_SpawnTimerUggWrongway = m_UggWrongwayInterval;
		m_SpawnTimerUggWrongway = 5.0f;

		if (gameInfo.gameMode == 3)
			m_VersusMode = true;

		m_pCoily = nullptr;

		m_SpawnUggWrongway = true;
	}

	void EnemyManager::Update()
	{
		m_pCurrentScene->GetTimer();
		float elapsed = m_pCurrentScene->GetTimer().GetElapsed();

		//UpdateCoilySpawnTimers(elapsed);
		//UpdateSlickSamSpawnTimers(elapsed);
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
		m_SpawnCoily = true;
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
			pEnemy->GetComponent<DeathComponent>()->OnDeath();
			pEnemy->GetComponent<GridNavigator>()->SetDead();
		}

		m_pEnemies.clear();
		m_SpawnCoily = true;
		m_SpawnSlickSam = true;
		m_SpawnUggWrongway = true;

		m_SpawnTimerCoily = m_CoilyInterval;
		m_SpawnTimerSlickSam = m_SlickSamInterval;
		m_SpawnTimerUggWrongway = m_UggWrongwayInterval;

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
		else if (enemyType == CharacterType::Ugg)
			m_CurrentUggWrongway--;
		else if (enemyType == CharacterType::Coily)
			m_pCoily = nullptr;


		pEnemy->GetComponent<DeathComponent>()->OnDeath();
		pEnemy->GetComponent<GridNavigator>()->SetDead();
	}

	void EnemyManager::Reset()
	{
		DestroyAllEnemies();
	}

	void EnemyManager::UpdateCoilySpawnTimers(float elapsedSec)
	{
		if (m_pCoily != nullptr)
			return;
		
		if (m_SpawnCoily)
		{
			m_SpawnTimerCoily -= elapsedSec;
			if (m_SpawnTimerCoily <= 0.f)
			{
				m_SpawnTimerCoily = m_CoilyInterval;
				m_SpawnTimerCoily = 10.0f;
				SpawnCoily();
			}
		}
	}

	void EnemyManager::UpdateSlickSamSpawnTimers(float elapsedSec)
	{
		if (m_MaxSlickSam <= m_CurrentSlickSam)
		{
			m_SpawnSlickSam = false;
		}
		else
		{
			m_SpawnSlickSam = true;
		}
		if (m_SpawnSlickSam)
		{
			m_SpawnTimerSlickSam -= elapsedSec;
			//if (m_SpawnTimerSlickSam <= 0.f)
			if (m_SpawnTimerSlickSam <= 0.f)
			{
				//m_SpawnSlickSam = false;
				m_SpawnTimerSlickSam = 2.0f;
				SpawnSlickSam();
			}
		}
	}

	void EnemyManager::UpdateUggWrongwaySpawnTimers(float elapsedSec)
	{
		if (m_MaxUggWrongway <= m_CurrentUggWrongway)
		{
			m_SpawnUggWrongway = false;
		}
		if (m_SpawnUggWrongway)
		{
			m_SpawnTimerUggWrongway -= elapsedSec;
			if (m_SpawnTimerUggWrongway <= 0.f)
			{
				//m_SpawnUggWrongway = false;
				m_SpawnTimerUggWrongway = 2.0f;
				SpawnUggWrongway();
			}
		}
	}

	void EnemyManager::SpawnCoily()
	{
		if(!m_VersusMode)
			m_pCoily = &GameObjectFactory::GetInstance().CreateCoily(*m_pCurrentScene, *m_pGrid);
		else
			m_pCoily = &GameObjectFactory::GetInstance().InitializePlayerTwo(*m_pCurrentScene, *m_pGrid, true);
	}

	void EnemyManager::SpawnSlickSam()
	{
		auto& enemy = GameObjectFactory::GetInstance().CreateSlickSam(*m_pCurrentScene, *m_pGrid);
		m_pEnemies.push_back(&enemy);
		m_CurrentSlickSam++;
	}

	void EnemyManager::SpawnUggWrongway()
	{
		GameObjectFactory::GetInstance().CreateUggWrongway(*m_pCurrentScene, *m_pGrid);
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

