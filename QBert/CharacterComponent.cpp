#include "CharacterComponent.h"
#include "TextureComponent.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"
#include "GameObject.h"
#include <memory>
#include "FacingStates.h"
#include "DeathComponent.h"


namespace dae
{
	CharacterComponent::CharacterComponent(GameObject& pOwner, const std::string& texFile, const std::string& charName, CharacterType charType)
		: BaseComponent(pOwner),
		m_Name{charName},
		m_Type{ charType }
	{

		//only sued for qbert as of monday
		auto sprite = std::make_unique<TextureComponent>(pOwner, texFile, 4);
		sprite.get()->SetSegments(0);
		m_Sprite = sprite.get();

		GetOwner()->AddComponent(std::move(sprite));



		m_pGameStates = std::make_unique<LeftDown>();


		if(GetOwner()->GetParent())
		{
			auto death = std::make_unique<DeathComponent>(*GetOwner()->GetParent());
			m_DeathComponent = death.get();
			GetOwner()->AddComponent(std::move(death));
		}
		else
		{
			auto death = std::make_unique<DeathComponent>(pOwner);
			m_DeathComponent = death.get();
			GetOwner()->AddComponent(std::move(death));
		}

	}

	CharacterComponent::CharacterComponent(GameObject& pOwner, CharacterType charType)
		: BaseComponent(pOwner),
		m_Type{ charType }
	{
		m_pGameStates = std::make_unique<LeftDown>();
		auto sprite = std::make_unique<TextureComponent>(pOwner);
		sprite.get()->SetSegments(0);
		m_Sprite = sprite.get();
		GetOwner()->AddComponent(std::move(sprite));

		auto death = std::make_unique<DeathComponent>(*GetOwner());
		m_DeathComponent = death.get();
		GetOwner()->AddComponent(std::move(death));

	}

	CharacterComponent::~CharacterComponent()
	{

	}
	void CharacterComponent::Render()
	{

	}
	void CharacterComponent::Update()
	{

	}

	void CharacterComponent::HandleInput(glm::vec2& input)
	{
		std::unique_ptr newState = std::move(m_pGameStates->HandleInput(GetOwner(), input));
		if(newState)
		{
			m_pGameStates = std::move(newState);  // m_pGameStates must be declared as std::unique_ptr<GameStates>
			m_pGameStates->Enter();
		}
	}

	CharacterType CharacterComponent::GetType()
	{
		return m_Type;
	}

	void CharacterComponent::SetType(CharacterType type)
	{
		type;
	}

	TextureComponent* CharacterComponent::InitializeSprite(const std::string& texFile, int segments)
	{
		//in case he already has it, remove it
		//GetOwner()->RemoveComponent(m_Sprite);

		auto text = ResourceManager::GetInstance().GetTexture(texFile);
		m_Sprite->SetTexture(text, segments);
		//auto sprite = std::make_unique<TextureComponent>(*GetOwner(), texFile, segments);
		m_Sprite->SetSegments(0);
		//m_Sprite = sprite.get();
		m_Sprite->SetScale({ 2,2 });

		m_pGameStates = std::make_unique<LeftDown>();

		//GetOwner()->AddComponent(std::move(sprite));
		return m_Sprite;
	}


}

