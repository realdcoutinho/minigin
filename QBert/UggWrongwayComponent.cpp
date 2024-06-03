#include "UggWrongwayComponent.h"
#include "CharacterComponent.h"
#include "TricklePathComponent.h"
#include "TriangularGrid.h"
#include "GridNavigator.h"
#include "GridNode.h"
#include "GameObject.h"
#include <random>

dae::UggWrongwayComponent::UggWrongwayComponent(GameObject& pOwner, TriangularGrid& grid)
	:BaseComponent(pOwner)
	, m_Character(nullptr)
	, m_TricklePath(nullptr)
	, m_UggTexture("Ugg.png")
	, m_WrongwayTexture("Wrongway.png")
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::bernoulli_distribution d(0.5);

	if (d(gen))
	{
		auto character = std::make_unique<CharacterComponent>(pOwner, CharacterType::Ugg);
		m_Character = character.get();
		GetOwner()->AddComponent(std::move(character));
		auto tex = m_Character->InitializeSprite(m_UggTexture, 4);
		tex->SetScale({ 2.0f, 2.0f });

		auto& node = grid.GetNode(37);
		std::unique_ptr<GridNavigator> gridNavigator = std::make_unique<GridNavigator>(pOwner, grid, node);
		m_Character->SetNavigator(gridNavigator.get());
		pOwner.AddComponent(std::move(gridNavigator));

		std::unique_ptr<TricklePathComponent> trickle = std::make_unique<TricklePathComponent>(pOwner, TrickleType::Right);
		m_TricklePath = trickle.get();
		pOwner.AddComponent(std::move(trickle));

		pOwner.SetLocalPosition(node.GetNodeInfo().centerPos);
	}
	else
	{
		auto character = std::make_unique<CharacterComponent>(pOwner, CharacterType::Wrongway);
		m_Character = character.get();
		GetOwner()->AddComponent(std::move(character));
		auto tex = m_Character->InitializeSprite(m_WrongwayTexture, 4);
		tex->SetScale({ 2.0f, 2.0f });

		auto& node = grid.GetNode(43);
		std::unique_ptr<GridNavigator> gridNavigator = std::make_unique<GridNavigator>(pOwner, grid, node);
		m_Character->SetNavigator(gridNavigator.get());
		pOwner.AddComponent(std::move(gridNavigator));

		std::unique_ptr<TricklePathComponent> trickle = std::make_unique<TricklePathComponent>(pOwner, TrickleType::Left);
		m_TricklePath = trickle.get();
		pOwner.AddComponent(std::move(trickle));

		pOwner.SetLocalPosition(node.GetNodeInfo().centerPos);
	}


}

dae::UggWrongwayComponent::~UggWrongwayComponent()
{
}

void dae::UggWrongwayComponent::Render()
{
}

void dae::UggWrongwayComponent::Update()
{
}