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

namespace dae
{
	QBertComponent::QBertComponent(GameObject& pOwner, TriangularGrid& pGrid, int startingNode, int player)
		: BaseComponent(pOwner)
	{
		auto score = std::make_unique<ScoreComponent>(pOwner);
		auto health = std::make_unique<HealthComponent>(pOwner, 3);

		m_Score = score.get();
		m_Health = health.get();

		GetOwner()->AddComponent(std::move(score));
		GetOwner()->AddComponent(std::move(health));

		auto character = std::make_unique<CharacterComponent>(pOwner, CharacterType::QBert);
		m_Character = character.get();
		GetOwner()->AddComponent(std::move(character));
		if(player == 1)
		{
			auto tex = m_Character->InitializeSprite(m_QBertTextureFile1, 4);
			tex->SetScale({ 2.0f, 2.0f });
		}
		else
		{
			auto tex = m_Character->InitializeSprite(m_QBertTextureFile2, 4);
			tex->SetScale({ 2.0f, 2.0f });
		}



		auto& node = pGrid.GetNode(startingNode);
		std::unique_ptr<GridNavigator> gridNavigator = std::make_unique<GridNavigator>(pOwner, pGrid, node);
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

