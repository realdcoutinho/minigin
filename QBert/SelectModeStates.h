#pragma once
#include "State.h"
#include <memory>
#include <glm/glm.hpp>
#include <string>

namespace dae
{
	class GameObject;
	class QBertGameMode;
	class SelectModeStates : public IState
	{
	public:
		SelectModeStates() = default;
		SelectModeStates(GameObject* character, const glm::vec2& input);
		virtual ~SelectModeStates() = default;
		virtual std::unique_ptr<SelectModeStates> HandleInput(GameObject* character, const glm::vec2& input) = 0;
		virtual void Enter() override;
		virtual void Update() override = 0;
		virtual void Exit() override = 0;
		virtual void SelectGameMode() = 0;
	protected:
		GameObject* m_ArrowHead;
		glm::vec2 m_Input;

		std::string m_SoloMode{ "LevelOneSolo" };
		std::string m_CoopMode{ "LevelOneCoop" };
		std::string m_VersusMode{ "LevelOneVS" };
		std::string m_QuitMode{ "Quit" };


		QBertGameMode* m_GameMode;
	};

	class SoloMode final : public SelectModeStates
	{
		public:
		SoloMode() = default;
		SoloMode(GameObject* character)
			: SelectModeStates(character, glm::vec2{ 0,0 })
		{
		}
		SoloMode(GameObject* character, const glm::vec2& input)
			: SelectModeStates(character, input)
		{
		}
		virtual ~SoloMode() = default;
		virtual std::unique_ptr<SelectModeStates> HandleInput(GameObject* character, const glm::vec2& input) override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
		virtual void SelectGameMode() override;
	};
	
	class CoopMode final : public SelectModeStates
	{
		public:
		CoopMode() = default;
		CoopMode(GameObject* character, const glm::vec2& input)
			: SelectModeStates(character, input)
		{
		}
		virtual ~CoopMode() = default;
		virtual std::unique_ptr<SelectModeStates> HandleInput(GameObject* character, const glm::vec2& input) override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
		virtual void SelectGameMode() override;
	};

	class VersusMode final : public SelectModeStates
	{
		public:
		VersusMode() = default;
		VersusMode(GameObject* character, const glm::vec2& input)
			: SelectModeStates(character, input)
		{
		}
		virtual ~VersusMode() = default;
		virtual std::unique_ptr<SelectModeStates> HandleInput(GameObject* character, const glm::vec2& input) override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
		virtual void SelectGameMode() override;
	};

	class QuitMode final : public SelectModeStates
	{
	public:
		QuitMode() = default;
		QuitMode(GameObject* character, const glm::vec2& input)
			: SelectModeStates(character, input)
		{
		}
		virtual ~QuitMode() = default;
		virtual std::unique_ptr<SelectModeStates> HandleInput(GameObject* character, const glm::vec2& input) override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
		virtual void SelectGameMode() override;
	};
}



