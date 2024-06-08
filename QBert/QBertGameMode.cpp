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
#include "LevelState.h"
#include "ServiceLocator.h"
#include "SoundLibrary.h"

namespace dae
{
	QBertGameMode::QBertGameMode(const std::string& name)
	{
		name;

		CreateTitleScenes();
		CreateInstructionsScenes();
		CreatePauseScreen();
		m_pEnemyManager = std::make_shared<EnemyManager>();
		m_pLevelState = std::make_shared<LevelState>();
	}

	void QBertGameMode::Update(float elapsed)
	{
		elapsed;
		m_pEnemyManager->Update();
		m_pLevelState->Update();
	}

	void QBertGameMode::LoadStartScene()
	{
		auto& sm = SceneManager::GetInstance();
		//sm.DestroyAllScenes();
		auto& startScene = sm.CreateScene("StartScene");
		sm.SetActiveScene(startScene);
		m_pCurrentScene = &sm.GetActiveScene();

		GameObjectFactory::GetInstance().CreateStartMenu(startScene);
	}

	void QBertGameMode::Restart()
	{
		m_PlayerOneLives = 3;
		m_PlayerTwoLives = 3;
		m_PlayerOneScore = 0;
		m_PlayerTwoScore = 0;
		m_pEnemyManager->Reset();
		m_pPlayers.clear();
		m_pEnemyListener.reset();
		//std::string restart{ "Restart" };
		//SetLevelState(restart);
		m_pLevelState = std::make_shared<LevelState>();
		LoadStartScene();
	}


	void QBertGameMode::StartScene(const std::string sceneName)
	{
		auto& sm = SceneManager::GetInstance();
		m_CurrentSceneName = sceneName;
		sm.SetActiveScene(sceneName);
		m_pCurrentScene = &sm.GetActiveScene();

	}

	void QBertGameMode::LoadScene(const std::string sceneName)
	{
		std::cout << "QBertGameMode started scene " << sceneName << std::endl;
		auto& sm = SceneManager::GetInstance();
		auto& scene = sm.CreateScene(sceneName);
		sm.SetActiveScene(scene);


		m_CurrentGameInfo = m_pGameInfoLoader->GetGameInfo(sceneName);
		auto& grid = GameObjectFactory::GetInstance().CreateGrid(scene, m_CurrentGameInfo);
		m_pGrid = grid.GetComponent<TriangularGrid>();

		m_pEnemyManager->SetNewData(m_CurrentGameInfo);
		m_pEnemyManager->SetTriangularGrid(*m_pGrid);
		m_pEnemyManager->SetCurrentScene(&scene);

		m_pEnemyListener = std::make_shared<EnemyListener>(m_pEnemyManager.get());
		EventDispatcher::GetInstance().SubscribeListener(m_pEnemyListener);

		CreatePlayers(scene);
	}

	void QBertGameMode::GameOver()
	{
		auto& sm = SceneManager::GetInstance();
		auto& scene = sm.CreateScene("Game Over");
		sm.SetActiveScene(scene);

		GameObjectFactory::GetInstance().CreateGameOver(scene, m_PlayerOneScore, m_PlayerTwoScore);
	}



	void QBertGameMode::VictoryScene()
	{
		auto& sm = SceneManager::GetInstance();
		auto& scene = sm.CreateScene("Victory Scene");
		sm.SetActiveScene(scene);

		GameObjectFactory::GetInstance().CreateVictoryScene(scene, m_PlayerOneScore, m_PlayerTwoScore);
	}


	void QBertGameMode::LoadNextScene()
	{
		m_pEnemyManager->Reset();
		m_pPlayers.clear();
		m_pEnemyListener.reset();
		m_pCurrentScene = nullptr;
		m_pGrid = nullptr;

		m_pLevelState->NextLevel();
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
	void QBertGameMode::ResetEnemyManager()
	{
		m_pEnemyManager->Reset();
	}

	void QBertGameMode::SetPlayerLives(int lives, int player)
	{
		if (player == 1)
		{
			m_PlayerOneLives = lives;
		}
		else if (player == 2)
		{
			m_PlayerTwoLives = lives;
		}
	}

	void QBertGameMode::SetPlayerScore(int score, int player)
	{
		if (player == 1)
		{
			m_PlayerOneScore = score;
		}
		else if (player == 2)
		{
			m_PlayerTwoScore = score;
		}
	}

	void QBertGameMode::SetLevelState(std::string& startScene)
	{
		auto levelState = m_pLevelState->HandleInput(startScene);
		if (levelState)
		{
			m_pLevelState->Exit();
			m_pLevelState = levelState;
			m_pLevelState->Enter();
		}
	}

	void QBertGameMode::StartGame()
	{
		m_pLevelState->NextLevel();
	}

	void QBertGameMode::PauseGame()
	{
		std::string pause{ "PauseScreen" };
		SetLevelState(pause);
	}

	void QBertGameMode::PlayerDied()
	{
		std::string over{ "Game Over" };
		SetLevelState(over);
	}



	void QBertGameMode::SetTitleScene(const std::string& startScene)
	{
		auto& sm = SceneManager::GetInstance();
		auto& scene = sm.GetSceneByName(startScene);
		sm.SetActiveScene(scene);

	}

	void QBertGameMode::CreatePlayers(Scene& scene)
	{
		if(m_PlayerOneLives > 0)	
		{
			auto& playerOne = GameObjectFactory::GetInstance().InitializePlayerOne(scene, *m_pGrid, m_CurrentGameInfo);
			m_pPlayers.push_back(&playerOne);
		}
		if (m_CurrentGameInfo.gameMode > 1)
		{
			if(m_PlayerTwoLives > 0)
			{
				auto& playerTwo = GameObjectFactory::GetInstance().InitializePlayerTwo(scene, *m_pGrid, m_CurrentGameInfo);
				m_pPlayers.push_back(&playerTwo);
			}
		}
	}
	void QBertGameMode::CreateTitleScenes()
	{
		auto& sm = SceneManager::GetInstance();
		auto& sceneOne = sm.CreateScene("LevelOneTitle");
		GameObjectFactory::GetInstance().CreateLevelOneTitle(sceneOne);

		auto& sceneTwo = sm.CreateScene("LevelTwoTitle");
		GameObjectFactory::GetInstance().CreateLevelTwoTitle(sceneTwo);

		auto& sceneThree = sm.CreateScene("LevelThreeTitle");
		GameObjectFactory::GetInstance().CreateLevelThreeTitle(sceneThree);
	}

	void QBertGameMode::CreateInstructionsScenes()
	{
		auto& sm = SceneManager::GetInstance();
		auto& sceneOne = sm.CreateScene("LevelSoloInstructions");
		GameObjectFactory::GetInstance().CreateLevelSoloInstructions(sceneOne);

		auto& sceneTwo = sm.CreateScene("LevelCoopInstructions");
		GameObjectFactory::GetInstance().CreateLevelCoopInstructions(sceneTwo);

		auto& sceneThree = sm.CreateScene("LevelVSInstructions");
		GameObjectFactory::GetInstance().CreateLevelVSInstructions(sceneThree);
	}
	void QBertGameMode::CreatePauseScreen()
	{
		auto& sm = SceneManager::GetInstance();
		auto& pauseScreen = sm.CreateScene("PauseScreen");
		GameObjectFactory::GetInstance().CreatePauseScreen(pauseScreen);
	}
}

