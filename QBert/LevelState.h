#pragma once
#include "State.h"
#include <memory>
#include <string>
#include <typeindex> // Include for std::type_index


namespace dae
{
	class GameObject;
	class QBertGameMode;
	class LevelState : public IState
	{
	public:
		LevelState() = default;
		LevelState(std::string& nextScene);
		virtual ~LevelState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override {};
		virtual void Update() override;
		virtual void Exit() override {};

		virtual void NextLevel() {};
	protected:
		bool m_FromPaused{ false };

		std::string m_CurrentScene;
		std::string m_PreviousScene;
		std::string m_PauseScreen{ "PauseScreen" };
		std::string m_Restart{ "Restart" };
		std::string m_GameOver{ "Game Over" };

		QBertGameMode* m_GameMode;

		const float m_TimeSwitch{ 3.0f };
		float m_CurrentTime{ 0.0f };
		bool m_Activate{ false };
	};

	class LevelInstructionsState final  : public LevelState
	{
	public:
		LevelInstructionsState() = default;
		LevelInstructionsState(std::string nextScene)
			: LevelState(nextScene)
		{

		}

		virtual ~LevelInstructionsState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

		virtual void NextLevel();
	protected:
		std::string m_LevelSoloInstructions{ "LevelSoloInstructions" };
		std::string m_LevelCoopInstructions{ "LevelCoopInstructions" };
		std::string m_LevelVSInstructions{ "LevelVSInstructions" };
	};


	class LevelOneState final : public LevelState
	{
	public:
		LevelOneState() = default;
		LevelOneState(std::string nextScene, bool fromPaused = false)
			: LevelState(nextScene)
		{
			m_FromPaused = fromPaused;
		}

		virtual ~LevelOneState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override ;
		virtual void Update() override ;
		virtual void Exit() override;

		virtual void NextLevel() override;

	private:
		const std::string m_LevelTitle{ "LevelOneTitle" };
		std::string m_LevelTwoSolo{ "LevelTwoSolo" };
		std::string m_LevelTwoCoop{ "LevelTwoCoop" };
		std::string m_LevelTwoVS{ "LevelTwoVS" };
	};

	class LevelTwoState final : public LevelState
	{
	public:
		LevelTwoState() = default;
		LevelTwoState(std::string nextScene, bool fromPaused = false)
			: LevelState(nextScene)
		{
			m_FromPaused = fromPaused;
		}
		virtual ~LevelTwoState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

		virtual void NextLevel() override;

	private:
		const std::string m_LevelTitle{ "LevelTwoTitle" };
		std::string m_LevelThreeSolo{ "LevelThreeSolo" };
		std::string m_LevelThreeCoop{ "LevelThreeCoop" };
		std::string m_LevelThreeVS{ "LevelThreeVS" };

	};

	class LevelThreeState final : public LevelState
	{
	public:
		LevelThreeState() = default;
		LevelThreeState(std::string nextScene, bool fromPaused = false)
			: LevelState(nextScene)
		{
			m_FromPaused = fromPaused;
		}
		virtual ~LevelThreeState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

		virtual void NextLevel() override;
	private:
		const std::string m_LevelTitle{ "LevelThreeTitle" };
		std::string m_VictoryScene{ "Victory Scene" };

	};

	class GameOverState final : public LevelState
	{
	public:
		GameOverState() = default;
		GameOverState(std::string& nextScene)
			: LevelState(nextScene)
		{

		}
		virtual ~GameOverState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

		virtual void NextLevel() override;
	};

	class GameCompleteState final : public LevelState
	{
	public:
		GameCompleteState() = default;
		GameCompleteState(std::string& nextScene)
			: LevelState(nextScene)
		{

		}
		virtual ~GameCompleteState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

		virtual void NextLevel() override;
	};

	class GamePauseState final : public LevelState
	{
	public:
		GamePauseState() = default;
		GamePauseState(std::type_index state, std::string& nextScene, std::string& previousScene)
			: LevelState(nextScene),
			m_IncomingState(state)
		{
			m_PreviousScene = previousScene;
		}

		virtual ~GamePauseState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

		virtual void NextLevel() override;

	private:
		std::type_index m_IncomingState;
	};


}

