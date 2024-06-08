#include "SelectModeStates.h"
#include "GameObject.h"
#include "GameModeManager.h"
#include "GameMode.h"
#include "QBertGameMode.h"
#include "ServiceLocator.h"
#include "AudioSystem.h"
#include "SoundLibrary.h"

namespace dae
{
	SelectModeStates::SelectModeStates(GameObject* character, const glm::vec2& input)
		:m_ArrowHead{ character }
		, m_Input{ input }
	{
		auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
		auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
		if (qbertGameMode)
			m_GameMode = qbertGameMode;
	}

	void SelectModeStates::Enter()
	{
		auto& soundSystem = dae::ServiceLocator::GetAudioService();
		soundSystem->PlaySound(static_cast<unsigned short>(SoundID::ChangeSelection), 1);
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
		SelectModeStates::Enter();
		m_ArrowHead->SetLocalPosition({ 150, 250 });
	}

	void SoloMode::Update()
	{
	}

	void SoloMode::Exit()
	{
	}

	void SoloMode::SelectGameMode()
	{
		//m_GameMode->LoadScene(m_SoloMode);
		m_GameMode->SetLevelState(m_SoloMode);
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
		SelectModeStates::Enter();
		m_ArrowHead->SetLocalPosition({ 150, 300 });
	}

	void CoopMode::Update()
	{
	}

	void CoopMode::Exit()
	{
	}

	void CoopMode::SelectGameMode()
	{
		//m_GameMode->LoadScene(m_CoopMode);
		m_GameMode->SetLevelState(m_CoopMode);

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
		SelectModeStates::Enter();
		m_ArrowHead->SetLocalPosition({ 150, 350 });
	}

	void VersusMode::Update()
	{
	}

	void VersusMode::Exit()
	{
	}

	void VersusMode::SelectGameMode()
	{
		//m_GameMode->LoadScene(m_VersusMode);
		m_GameMode->SetLevelState(m_VersusMode);
	}




}
