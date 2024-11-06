#include "EnemyCharacterComponent.h"
#include "GameObject.h"
#include "GridNavigator.h"
#include <memory>
#include "CharacterComponent.h"
#include "ResourceManager.h"
#include "TricklePathComponent.h"
#include "GridNavigator.h"
#include "TriangularGrid.h"


namespace dae
{
	EnemyCharacterComponent::EnemyCharacterComponent(GameObject& pOwner, const std::string& texFile, const std::string& charName, CharacterType charType, TriangularGrid& grid)
		: CharacterComponent(pOwner, texFile, charName, charType)
	{

		auto node = grid.GetNode(4);
		std::unique_ptr<GridNavigator> gridNavigator = std::make_unique<GridNavigator>(pOwner, grid, *node);
		m_Navigator = gridNavigator.get();  // m_Navigator must be declared as GridNavigator*
		pOwner.AddComponent(std::move(gridNavigator));

		std::unique_ptr<TricklePathComponent> trickle = std::make_unique<TricklePathComponent>(pOwner, TrickleType::Down);
		m_TricklePath = trickle.get();
		pOwner.AddComponent(std::move(trickle));

		if (m_Type == CharacterType::Slick)
		{
			m_Sprite->SetScale({ 2.0f, 2.0f });
		}
		else
		{
			auto sprite = m_Sprite->GetSDLTexture();
			m_Sprite->SetTexture(sprite, 1);
			SetTextures();

		}



	}

	EnemyCharacterComponent::~EnemyCharacterComponent()
	{
	}

	void EnemyCharacterComponent::Render()
	{
	}

	void EnemyCharacterComponent::Update()
	{
	}

	void EnemyCharacterComponent::HandleInput(glm::vec2& input)
	{
		CharacterComponent::HandleInput(input);
	}

	void EnemyCharacterComponent::SetTextures()
	{
		switch (m_Type)
		{
		case CharacterType::Coily:
		{
			auto tex = ResourceManager::GetInstance().GetTexture("Snake.png");
			if(tex != nullptr)
				m_Sprite->SetTexture(tex);
			break;
		}
		case CharacterType::Ugg:
		{
			auto tex = ResourceManager::GetInstance().GetTexture("Egg.png");
			m_Sprite->SetTexture(tex);
			break;
		}
		case CharacterType::Wrongway:
		{
			auto tex = ResourceManager::GetInstance().GetTexture("Egg.png");
			m_Sprite->SetTexture(tex);
			break;
		}
		//case CharacterType::Slick:
		//{
		//	auto tex = ResourceManager::GetInstance().GetTexture("Slick.png");
		//	m_Sprite->SetTexture(tex);
		//	break;
		//}
		//case CharacterType::Sam:
		//{
		//	auto tex = ResourceManager::GetInstance().GetTexture("Egg.png");
		//	m_Sprite->SetTexture(tex);
		//	break;
		//}
		case CharacterType::Egg:
		{
			auto tex = ResourceManager::GetInstance().GetTexture("Egg.png");
			m_Sprite->SetTexture(tex);
			break;
		}
		}
	}
}

