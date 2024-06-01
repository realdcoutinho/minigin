//#pragma once
//#include <memory>
//#include <string>
//#include "Subject.h"
//#include "BaseComponent.h"
//
//
//namespace dae
//{
//	class TextureComponent;
//	class ScoreComponent;
//	class HealthComponent;
//
//	class CharacterComponent : public BaseComponent
//	{
//
//	public:
//		CharacterComponent(GameObject& pOwner, const std::string& texFile, const std::string& charName);
//		~CharacterComponent();
//
//		CharacterComponent(const CharacterComponent&) = delete;
//		CharacterComponent(CharacterComponent&&) = delete;
//		CharacterComponent& operator= (const CharacterComponent&) = delete;
//		CharacterComponent& operator= (const CharacterComponent&&) = delete;
//
//		void Render() override;
//		void Update() override;
//
//		int GetHealthValue() const;
//		int GetScoreValue() const;
//
//	private:
//		TextureComponent* m_Sprite;
//		ScoreComponent* m_Score;
//		HealthComponent* m_Health;
//
//		std::string m_Name;
//	};
//
//
//}
