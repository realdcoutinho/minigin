#include "LevelState.h"
#include "GameModeManager.h"
#include "GameMode.h"
#include "QBertGameMode.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TimeManager.h"


namespace dae 
{
	LevelState::LevelState(std::string& nextScene)
		: m_CurrentScene(nextScene)
	{
		auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
		auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
		if (qbertGameMode)
			m_GameMode = qbertGameMode;

		m_Activate = true;
	}

	std::shared_ptr<LevelState> LevelState::HandleInput(std::string& nextScene)
	{
		return std::make_shared<LevelOneState>(nextScene);
	}

	void LevelOneState::Enter()
	{
		m_GameMode->SetTitleScene(m_LevelTitle);
		//auto& sm = SceneManager::GetInstance();
		//auto scene = sm.GetSceneByName(m_LevelTitle);
		//sm.SetActiveScene(scene);


	}

	void LevelOneState::Update()
	{
		if(m_Activate)
		{
			m_CurrentTime += TimeManager::GetInstance().GlobalElapsed();
			if (m_CurrentTime >= m_TimeSwitch)
			{
				m_GameMode->LoadScene(m_CurrentScene);
				m_Activate = false;
			}
		}
	}

	void LevelOneState::Exit()
	{
	}

	void LevelOneState::NextLevel()
	{
		if (m_CurrentScene == "LevelOneSolo")
			m_GameMode->SetLevelState(m_LevelTwoSolo);
		if(m_CurrentScene == "LevelOneCoop")
			m_GameMode->SetLevelState(m_LevelTwoCoop);
		if(m_CurrentScene == "LevelOneVS")
			m_GameMode->SetLevelState(m_LevelTwoVS);
	}

	std::shared_ptr<LevelState> LevelOneState::HandleInput(std::string& nextScene)
	{
		return std::make_shared<LevelTwoState>(nextScene);
	}

	std::shared_ptr<LevelState> LevelTwoState::HandleInput(std::string& nextScene)
	{
		return std::make_shared<LevelTwoState>(nextScene);
	}

	void LevelTwoState::Enter()
	{
		m_GameMode->SetTitleScene(m_LevelTitle);
	}

	void LevelTwoState::Update()
	{
		if (m_Activate)
		{
			m_CurrentTime += TimeManager::GetInstance().GlobalElapsed();
			if (m_CurrentTime >= m_TimeSwitch)
			{
				m_GameMode->LoadScene(m_CurrentScene);
				m_Activate = false;
			}
		}
	}

	void LevelTwoState::Exit()
	{
	}
	void LevelTwoState::NextLevel()
	{
	}
	std::shared_ptr<LevelState> LevelThreeState::HandleInput(std::string& nextScene)
	{
		nextScene;

		return std::shared_ptr<LevelThreeState>();
	}
	void LevelThreeState::Enter()
	{
	}
	void LevelThreeState::Update()
	{
	}
	void LevelThreeState::Exit()
	{
	}
	void LevelThreeState::NextLevel()
	{
	}
	std::shared_ptr<LevelState> GameOverState::HandleInput(std::string& nextScene)
	{
		nextScene;

		return std::shared_ptr<GameOverState>();
	}
	void GameOverState::Enter()
	{
	}
	void GameOverState::Update()
	{
	}
	void GameOverState::Exit()
	{
	}
	void GameOverState::NextLevel()
	{
	}
	std::shared_ptr<LevelState> GameCompleteState::HandleInput(std::string& nextScene)
	{
		nextScene;

		return std::shared_ptr<GameCompleteState>();
	}
	void GameCompleteState::Enter()
	{
	}
	void GameCompleteState::Update()
	{
	}
	void GameCompleteState::Exit()
	{
	}
	void GameCompleteState::NextLevel()
	{
	}
	std::shared_ptr<LevelState> GamePauseState::HandleInput(std::string& nextScene)
	{
		nextScene;

		return std::shared_ptr<GamePauseState>();
	}
	void GamePauseState::Enter()
	{
	}
	void GamePauseState::Update()
	{
	}
	void GamePauseState::Exit()
	{
	}

	void GamePauseState::NextLevel()
	{
	}

}


