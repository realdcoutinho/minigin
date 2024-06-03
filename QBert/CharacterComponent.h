#pragma once
#include <memory>
#include <string>
#include "Subject.h"
#include "BaseComponent.h"
#include "TriangularGrid.h"
#include "FacingStates.h"
#include <glm/glm.hpp>

namespace dae
{
	class TextureComponent;
	class DeathComponent;
	class GameStates;


	enum class CharacterType
	{
		QBert,
		Egg,
		Coily,
		Slick,
		Sam,
		Ugg,
		Wrongway,
	};

	class GridNavigator;
	class CharacterComponent : public BaseComponent
	{

	public:
		CharacterComponent(GameObject& pOwner, const std::string& texFile, const std::string& charName, CharacterType charType);
		CharacterComponent(GameObject& pOwner, CharacterType charType);
		~CharacterComponent();

		CharacterComponent(const CharacterComponent&) = delete;
		CharacterComponent(CharacterComponent&&) = delete;
		CharacterComponent& operator= (const CharacterComponent&) = delete;
		CharacterComponent& operator= (const CharacterComponent&&) = delete;

		void Render() override;
		void Update() override;

		virtual void HandleInput(glm::vec2& input);

		virtual CharacterType GetType();
		virtual void SetType(CharacterType type);

		//Navigator
		GridNavigator* GetNavigator() { return m_Navigator; }
		void SetNavigator(GridNavigator* navigator) { m_Navigator = navigator; }

		//Sprite
		TextureComponent* GetSprite() { return m_Sprite; }
		TextureComponent* InitializeSprite(const std::string& texFile, int segments);

	protected:
		TextureComponent* m_Sprite;
		GridNavigator* m_Navigator;
		DeathComponent* m_DeathComponent;
		CharacterType m_Type;

		std::unique_ptr<FacingStates> m_pGameStates;

		std::string m_Name;
	};


}
