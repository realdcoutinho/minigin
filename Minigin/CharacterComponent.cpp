//#include "CharacterComponent.h"
//#include "TextureComponent.h"
//#include "ScoreComponent.h"
//#include "HealthComponent.h"
//#include "GameObject.h"
//
//namespace dae
//{
//	CharacterComponent::CharacterComponent(GameObject& pOwner, const std::string& texFile, const std::string& charName)
//		: BaseComponent(pOwner),
//		m_Name{charName}
//	{
//
//		auto sprite = std::make_unique<TextureComponent>(pOwner, texFile);
//		auto score = std::make_unique<ScoreComponent>(pOwner);
//		auto health = std::make_unique<HealthComponent>(pOwner, 3);
//
//		m_Sprite = sprite.get();
//		m_Score = score.get();
//		m_Health = health.get();
//		GetOwner()->AddComponent(std::move(sprite));
//		GetOwner()->AddComponent(std::move(score));
//		GetOwner()->AddComponent(std::move(health));
//	}
//
//	CharacterComponent::~CharacterComponent()
//	{
//
//	}
//	void CharacterComponent::Render()
//	{
//
//	}
//	void CharacterComponent::Update()
//	{
//
//	}
//
//	int CharacterComponent::GetHealthValue() const
//	{ 
//		return m_Health->GetHealth(); 
//	}
//
//	int CharacterComponent::GetScoreValue() const
//	{ 
//		return m_Score->GetScore(); 
//	}
//}
//
