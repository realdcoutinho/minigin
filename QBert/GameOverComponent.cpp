#include "GameOverComponent.h"
#include "TextureComponent.h"
#include "TextComponent.h"
#include "QBertGameMode.h"
#include "GameModeManager.h"
#include "ResourceManager.h"
#include <memory>

namespace dae
{
	FinalScoreComponent::FinalScoreComponent(dae::GameObject& pOwner, int score1, int score2)
		:BaseComponent(pOwner)
		, m_Score1(score1)
		, m_Score2(score2)
	{
		auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
		auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
		if (qbertGameMode)
			m_pGameMode = qbertGameMode;

		if (m_Score1 > m_Score2)
		{
			const std::string score1string = m_Player1 + " Score: " + std::to_string(m_Score1);
			std::unique_ptr<TextComponent> component = std::make_unique<TextComponent>(pOwner, score1string, ResourceManager::GetInstance().GetFont("Minecraft.ttf", 36));
			m_pTextPlayerOne = component.get();
			pOwner.AddComponent(std::move(component));
		}
		if (m_Score2 > m_Score1)
		{
			const std::string score2string = m_Player2 + " Score: " + std::to_string(m_Score2);
			std::unique_ptr<TextComponent> component = std::make_unique<TextComponent>(pOwner, score2string, ResourceManager::GetInstance().GetFont("Minecraft.ttf", 36));
			m_pTextPlayerTwo = component.get();
			pOwner.AddComponent(std::move(component));
		}


	}
	void FinalScoreComponent::Render()
	{
	}
	void FinalScoreComponent::Update()
	{
	}
	void FinalScoreComponent::RestartGame()
	{
		m_pGameMode->Restart();
	}
}

