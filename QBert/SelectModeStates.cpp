#include "SelectModeStates.h"
#include "GameObject.h"
#include "GameModeManager.h"
#include "GameMode.h"
#include "QBertGameMode.h"

namespace dae
{
	SelectModeStates::SelectModeStates(GameObject* character, const glm::vec2& input)
		:m_Character{ character }
		, m_Input{ input }
	{
		auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
		auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
		if (qbertGameMode)
			m_GameMode = qbertGameMode;
	}

	std::unique_ptr<SelectModeStates> dae::SoloMode::HandleInput(GameObject* character, const glm::vec2& input)
	{
		if (input.x == 0 && input.y == -1)
		{
			return std::make_unique<CoopMode>(character, input);
		}
		if (input.x == 0 && input.y == 1)
		{
			return std::make_unique<VersusMode>(character, input);
		}
		return std::make_unique<SoloMode>(character, input);
	}

	void SoloMode::Enter()
	{
		m_Character->SetLocalPosition({ 150, 250 });
	}

	void SoloMode::Update()
	{
	}

	void SoloMode::Exit()
	{
	}

	void SoloMode::SelectGameMode()
	{
		m_GameMode->LoadScene(m_SoloMode);
	}

	std::unique_ptr<SelectModeStates> CoopMode::HandleInput(GameObject* character, const glm::vec2& input)
	{
		if (input.x == 0 && input.y == -1)
		{
			return std::make_unique<VersusMode>(character, input);
		}
		if (input.x == 0 && input.y == 1)
		{
			return std::make_unique<SoloMode>(character, input);
		}
		return std::make_unique<CoopMode>(character, input);
	}

	void CoopMode::Enter()
	{
		m_Character->SetLocalPosition({ 150, 300 });
	}

	void CoopMode::Update()
	{
	}

	void CoopMode::Exit()
	{
	}

	void CoopMode::SelectGameMode()
	{
		m_GameMode->LoadScene(m_CoopMode);
	}

	std::unique_ptr<SelectModeStates> VersusMode::HandleInput(GameObject* character, const glm::vec2& input)
	{
		if (input.x == 0 && input.y == 1)
		{
			return std::make_unique<CoopMode>(character, input);
		}
		if (input.x == 0 && input.y == -1)
		{
			return std::make_unique<SoloMode>(character, input);
		}
		return std::make_unique<VersusMode>(character, input);
	}

	void VersusMode::Enter()
	{
		m_Character->SetLocalPosition({ 150, 350 });
	}

	void VersusMode::Update()
	{
	}

	void VersusMode::Exit()
	{
	}

	void VersusMode::SelectGameMode()
	{
		m_GameMode->LoadScene(m_VersusMode);
	}




}