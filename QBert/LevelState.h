#pragma once
#include "State.h"
#include <memory>
#include <string>

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
		virtual void Update() override {};
		virtual void Exit() override {};

		virtual void NextLevel() {};
	protected:
		std::string m_CurrentScene;
		std::string m_PreviousScene;

		QBertGameMode* m_GameMode;

		const float m_TimeSwitch{ 3.0f };
		float m_CurrentTime{ 0.0f };
		bool m_Activate{ false };
	};

	class LevelOneState final : public LevelState
	{
	public:
		LevelOneState() = default;
		LevelOneState(std::string nextScene)
			: LevelState(nextScene)
		{

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
		LevelTwoState(std::string& nextScene)
			: LevelState(nextScene)
		{

		}
		virtual ~LevelTwoState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

		virtual void NextLevel() override;

	private:
		const std::string m_LevelTitle{ "LevelTwoTitle" };

	};

	class LevelThreeState final : public LevelState
	{
	public:
		LevelThreeState() = default;
		LevelThreeState(std::string& nextScene)
			: LevelState(nextScene)
		{

		}
		virtual ~LevelThreeState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

		virtual void NextLevel() override;
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
		GamePauseState(std::string& nextScene)
			: LevelState(nextScene)
		{

		}
		virtual ~GamePauseState() = default;
		virtual std::shared_ptr<LevelState> HandleInput(std::string& nextScene);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

		virtual void NextLevel() override;
	};


}

