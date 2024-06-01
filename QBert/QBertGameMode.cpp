#include "QBertGameMode.h"
#include "GameObjectFactory.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameInfoLoader.h"
#include "EnemyManager.h"
//#include "GameInfo.h"
#include "GridNode.h"
#include <iostream>
#include "TriangularGrid.h"
#include "Listeners.h"
#include "EventDispatcher.h"
#include "GameCommand.h"
#include "InputManager.h"
#include "Input.h"

namespace dae
{
	QBertGameMode::QBertGameMode(const std::string& name)
	{
		name;
		m_pEnemyManager = std::make_shared<EnemyManager>();
	}

	void QBertGameMode::Update(float elapsed)
	{
		elapsed;
		m_pEnemyManager->Update();
	}

	void QBertGameMode::StartScene(const std::string sceneName)
	{
		std::cout << "QBertGameMode started scene " << sceneName << std::endl;
		m_CurrentSceneName = sceneName;
		auto& sm = SceneManager::GetInstance();
		sm.SetActiveScene(sceneName);
		m_pCurrentScene = &sm.GetActiveScene();


		m_CurrentGameInfo = m_pGameInfoLoader->GetGameInfo(m_CurrentSceneName);
		auto& grid = GameObjectFactory::GetInstance().CreateGrid(*m_pCurrentScene, m_CurrentGameInfo);
		m_pGrid = grid.GetComponent<TriangularGrid>();

		m_pEnemyManager->SetNewData(m_CurrentGameInfo);
		m_pEnemyManager->SetTriangularGrid(*m_pGrid);
		m_pEnemyManager->SetCurrentScene(m_pCurrentScene);

		m_pEnemyListener = std::make_shared<EnemyListener>(m_pEnemyManager.get());
		EventDispatcher::GetInstance().SubscribeListener(m_pEnemyListener);



		auto& playerOne = GameObjectFactory::GetInstance().InitializePlayerOne(*m_pCurrentScene, *m_pGrid);
		m_pPlayers.push_back(&playerOne);
		auto& playerTwo = GameObjectFactory::GetInstance().InitializePlayerTwo(*m_pCurrentScene, *m_pGrid);
		m_pPlayers.push_back(&playerTwo);
	}

	void QBertGameMode::QBertMovement()
	{
		m_pEnemyManager->HuntQbert(m_pPlayers);
	}
	void QBertGameMode::CanBertRender(bool render)
	{
		for (auto player : m_pPlayers)
		{
			player->GetComponent<TextureComponent>()->SetRender(render);
		}

	}
}

