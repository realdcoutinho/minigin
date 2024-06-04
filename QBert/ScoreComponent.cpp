#include "ScoreComponent.h"
#include "ScoreComponent.h"
#include "Subject.h"
#include "EventManager.h"
#include "GameObject.h"
#include "BaseEvent.h"
#include "EventManager.h"
#include <memory>
#include "QbertEvents.h"
#include "EventDispatcher.h"
#include "GameModeManager.h"
#include "QBertGameMode.h"
#include "QBertComponent.h"


namespace dae
{
	ScoreComponent::ScoreComponent(GameObject& pOwner, int intialPoints)
		:BaseComponent(pOwner),
		m_Score{ intialPoints }
	{
		auto scoreEvent = std::make_unique<ScoreEventHUD>(m_Score, GetOwnerID());
		EventDispatcher::GetInstance().DispatchEvent(std::move(scoreEvent));
	}

	ScoreComponent::~ScoreComponent()
	{

	}

	void ScoreComponent::SetScore(int score)
	{
		m_Score += score;
		auto scoreEvent = std::make_unique<ScoreEventHUD>(m_Score, GetOwnerID());
		EventDispatcher::GetInstance().DispatchEvent(std::move(scoreEvent));

		auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
		auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
		if (qbertGameMode != nullptr)
		{
			qbertGameMode->GetGrid()->UnregisterAllCharacters();
			int playerNumber = GetOwner()->GetComponent<QBertComponent>()->GetPlayerNumber();
			qbertGameMode->SetPlayerScore(m_Score, playerNumber);
		}
	}

	int ScoreComponent::GetScore() const
	{
		return m_Score;

	}

	void ScoreComponent::Update()
	{

	}

	void ScoreComponent::Render()
	{

	}
}
