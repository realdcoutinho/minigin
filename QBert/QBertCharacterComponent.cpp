#include "QBertCharacterComponent.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"
#include "TriangularGrid.h"
#include "GridNavigator.h"
#include <memory>

dae::QBertCharacterComponent::QBertCharacterComponent(GameObject& pOwner, TriangularGrid& pGrid)
	: CharacterComponent(pOwner, "Qbert P1 Spritesheet.png", "QBert", CharacterType::QBert)
{
	auto score = std::make_unique<ScoreComponent>(pOwner);
	auto health = std::make_unique<HealthComponent>(pOwner, 3);

	m_Score = score.get();
	m_Health = health.get();

	GetOwner()->AddComponent(std::move(score));

	m_Sprite->SetScale({ 2.0f, 2.0f });

	auto& node = pGrid.GetStartingNode();
	std::unique_ptr<GridNavigator> gridNavigator = std::make_unique<GridNavigator>(pOwner, pGrid, node);

	m_Navigator = gridNavigator.get();  // m_Navigator must be declared as GridNavigator*
	pOwner.AddComponent(std::move(gridNavigator));

}

dae::QBertCharacterComponent::~QBertCharacterComponent()
{
}

void dae::QBertCharacterComponent::Render()
{
}

void dae::QBertCharacterComponent::Update()
{
}

int dae::QBertCharacterComponent::GetHealthValue() const
{
	return m_Health->GetHealth();
}

int dae::QBertCharacterComponent::GetScoreValue() const
{
	return m_Score->GetScore();
}

void dae::QBertCharacterComponent::HandleInput(glm::vec2& input)
{
	CharacterComponent::HandleInput(input);


}
