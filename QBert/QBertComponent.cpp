#include "QBertComponent.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "GridNavigator.h"
#include "TriangularGrid.h"
#include "QBertGameMode.h"
#include "GameModeManager.h"
#include "RespawnComponent.h"
#include "GameMode.h"
#include "GameInfo.h"
#include "GameInfoLoader.h"
#include "Scene.h"
#include "GameModeManager.h"
#include "QBertGameMode.h"

namespace dae
{
	QBertComponent::QBertComponent(GameObject& pOwner, TriangularGrid& pGrid, int startingNode, int player)
		: BaseComponent(pOwner),
		m_PlayerNumber{ player }
	{
		auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
		auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
		if (qbertGameMode == nullptr)	
			return;



		auto character = std::make_unique<CharacterComponent>(pOwner, CharacterType::QBert);
		m_Character = character.get();
		GetOwner()->AddComponent(std::move(character));


		int scorePoints{};
		int healthPoints{};
		if(player == 1)
		{
			scorePoints = qbertGameMode->GetPlayerOneScore();
			healthPoints = qbertGameMode->GetPlayerOneLives();
			auto tex = m_Character->InitializeSprite(m_QBertTextureFile1, 4);
			tex->SetScale({ 2.0f, 2.0f });
		}
		if(player == 2)
		{
			scorePoints = qbertGameMode->GetPlayerTwoScore();
			healthPoints = qbertGameMode->GetPlayerTwoLives();
			auto tex = m_Character->InitializeSprite(m_QBertTextureFile2, 4);
			tex->SetScale({ 2.0f, 2.0f });
		}


		auto score = std::make_unique<ScoreComponent>(pOwner, scorePoints);
		auto health = std::make_unique<HealthComponent>(pOwner, healthPoints);

		m_Score = score.get();
		m_Health = health.get();

		GetOwner()->AddComponent(std::move(score));
		GetOwner()->AddComponent(std::move(health));



		auto node = pGrid.GetNode(startingNode);
		std::unique_ptr<GridNavigator> gridNavigator = std::make_unique<GridNavigator>(pOwner, pGrid, *node);
		m_Character->SetNavigator(gridNavigator.get());
		pOwner.AddComponent(std::move(gridNavigator));


		auto respawn = std::make_unique<RespawnComponent>(pOwner);
		m_Respawn = respawn.get();
		pOwner.AddComponent(std::move(respawn));
	}
	QBertComponent::~QBertComponent()
	{
	}
	void QBertComponent::Render()
	{
	}
	void QBertComponent::Update()
	{
	}

	int QBertComponent::GetHealthValue() const
	{
		return m_Health->GetHealth();
	}

	int QBertComponent::GetScoreValue() const
	{
		return m_Score->GetScore();
	}
}

