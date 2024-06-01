#include "SamSlickComponent.h"
#include "CharacterComponent.h"
#include "TricklePathComponent.h"
#include "TriangularGrid.h"
#include "GridNavigator.h"
#include <random>


namespace dae
{
	SamSlickComponent::SamSlickComponent(GameObject& pOwner, TriangularGrid& grid)
		: BaseComponent(pOwner)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::bernoulli_distribution d(0.5);

		if (d(gen))
		{
			auto character = std::make_unique<CharacterComponent>(pOwner, CharacterType::Sam);
			m_Character = character.get();
			GetOwner()->AddComponent(std::move(character));
			auto tex = m_Character->InitializeSprite(m_SamTextureFile, 4);
			tex->SetScale({ 2.0f, 2.0f });

		}
		else
		{
			auto character = std::make_unique<CharacterComponent>(pOwner, CharacterType::Slick);
			m_Character = character.get();
			GetOwner()->AddComponent(std::move(character));
			auto tex = m_Character->InitializeSprite(m_SlickTextureFile, 4);
			tex->SetScale({ 2.0f, 2.0f });

		}

		auto& node = grid.GetNode(4);
		std::unique_ptr<GridNavigator> gridNavigator = std::make_unique<GridNavigator>(pOwner, grid, node);
		m_Character->SetNavigator(gridNavigator.get());
		pOwner.AddComponent(std::move(gridNavigator));

		std::unique_ptr<TricklePathComponent> trickle = std::make_unique<TricklePathComponent>(pOwner, TrickleType::Down);
		m_TricklePath = trickle.get();
		pOwner.AddComponent(std::move(trickle));
	}

	SamSlickComponent::~SamSlickComponent()
	{
	}

	void SamSlickComponent::Render()
	{
	}

	void SamSlickComponent::Update()
	{
	}

}
