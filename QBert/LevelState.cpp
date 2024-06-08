#include "LevelState.h"
#include "GameModeManager.h"
#include "GameMode.h"
#include "QBertGameMode.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TimeManager.h"
#include "ServiceLocator.h"
#include "AudioSystem.h"
#include "SoundLibrary.h"

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

		return std::make_shared<LevelInstructionsState>(nextScene);
	}

	void LevelState::Update()
	{
		if (m_FromPaused)
			return;
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


	std::shared_ptr<LevelState> LevelInstructionsState::HandleInput(std::string& nextScene)
	{
		return std::make_shared<LevelOneState>(nextScene);
	}

	void LevelInstructionsState::Enter()
	{

		if (m_CurrentScene == "LevelOneSolo")
			m_GameMode->SetTitleScene(m_LevelSoloInstructions);
		if (m_CurrentScene == "LevelOneCoop")
			m_GameMode->SetTitleScene(m_LevelCoopInstructions);
		if (m_CurrentScene == "LevelOneVS")
			m_GameMode->SetTitleScene(m_LevelVSInstructions);
	}

	void LevelInstructionsState::Update()
	{
	}

	void LevelInstructionsState::Exit()
	{
	}

	void LevelInstructionsState::NextLevel()
	{
		m_GameMode->SetLevelState(m_CurrentScene);
	}


	std::shared_ptr<LevelState> LevelOneState::HandleInput(std::string& nextScene)
	{
		if (nextScene == m_PauseScreen)
			return  std::make_shared<GamePauseState>(std::type_index(typeid(LevelOneState)), nextScene, m_CurrentScene);
		if (nextScene == m_GameOver)
			return std::make_shared<GameOverState>(nextScene);
		else
			return std::make_shared<LevelTwoState>(nextScene);
	}

	void LevelOneState::Enter()
	{
		if (m_FromPaused)
			m_GameMode->SetTitleScene(m_CurrentScene);
		else
		{
			auto& soundSystem = dae::ServiceLocator::GetAudioService();
			soundSystem->PlaySound(static_cast<unsigned short>(SoundID::LevelScreenTune), 1);
			m_GameMode->SetTitleScene(m_LevelTitle);
		}

	}

	void LevelOneState::Update()
	{
		LevelState::Update();
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



	std::shared_ptr<LevelState> LevelTwoState::HandleInput(std::string& nextScene)
	{
		if (nextScene == m_PauseScreen)
			return  std::make_shared<GamePauseState>(std::type_index(typeid(LevelTwoState)), nextScene, m_CurrentScene);
		if (nextScene == m_GameOver)
			return std::make_shared<GameOverState>(nextScene);
		else
			return std::make_shared<LevelThreeState>(nextScene);
	}

	void LevelTwoState::Enter()
	{
		if (m_FromPaused)
			m_GameMode->SetTitleScene(m_CurrentScene);
		else
		{
			auto& soundSystem = dae::ServiceLocator::GetAudioService();
			soundSystem->PlaySound(static_cast<unsigned short>(SoundID::LevelScreenTune), 1);
			m_GameMode->SetTitleScene(m_LevelTitle);
		}
	}

	void LevelTwoState::Update()
	{
		LevelState::Update();
	}

	void LevelTwoState::Exit()
	{
	}

	void LevelTwoState::NextLevel()
	{
		if (m_CurrentScene == "LevelTwoSolo")
			m_GameMode->SetLevelState(m_LevelThreeSolo);
		if (m_CurrentScene == "LevelTwoCoop")
			m_GameMode->SetLevelState(m_LevelThreeCoop);
		if (m_CurrentScene == "LevelTwoVS")
			m_GameMode->SetLevelState(m_LevelThreeVS);
	}



	std::shared_ptr<LevelState> LevelThreeState::HandleInput(std::string& nextScene)
	{
		if (nextScene == m_PauseScreen)
			return  std::make_shared<GamePauseState>(std::type_index(typeid(LevelThreeState)), nextScene, m_CurrentScene);
		if (nextScene == m_VictoryScene)
			return std::make_shared<GameCompleteState>(nextScene);
		if (nextScene == m_GameOver)
			return std::make_shared<GameOverState>(nextScene);
		else
			return std::make_shared<GameCompleteState>(nextScene);
	}

	void LevelThreeState::Enter()
	{
		if (m_FromPaused)
			m_GameMode->SetTitleScene(m_CurrentScene);
		else
		{
			auto& soundSystem = dae::ServiceLocator::GetAudioService();
			soundSystem->PlaySound(static_cast<unsigned short>(SoundID::LevelScreenTune), 1);
			m_GameMode->SetTitleScene(m_LevelTitle);
		}

	}

	void LevelThreeState::Update()
	{
		LevelState::Update();
	}

	void LevelThreeState::Exit()
	{
	}
	void LevelThreeState::NextLevel()
	{
		m_GameMode->SetLevelState(m_VictoryScene);
	}

	std::shared_ptr<LevelState> GameOverState::HandleInput(std::string& nextScene)
	{
		nextScene;

		return std::shared_ptr<GameOverState>();
	}

	void GameOverState::Enter()
	{
		m_GameMode->GameOver();
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
		m_GameMode->VictoryScene();
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
		if(nextScene == m_Restart)
			return std::make_shared<LevelState>();
		if (m_IncomingState == typeid(LevelOneState)) 
			return std::make_shared<LevelOneState>(m_PreviousScene, true);
		else if (m_IncomingState == typeid(LevelTwoState)) 
			return std::make_shared<LevelTwoState>(m_PreviousScene, true);
		else if (m_IncomingState == typeid(LevelThreeState))
			return std::make_shared<LevelThreeState>(m_PreviousScene, true);

		return std::shared_ptr<GamePauseState>();
	}
	void GamePauseState::Enter()
	{
		m_GameMode->SetTitleScene(m_CurrentScene);
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


