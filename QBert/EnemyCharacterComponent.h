#pragma once
#include "CharacterComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"




namespace dae
{
	class GridNavigator;
	class TricklePathComponent;

	class EnemyCharacterComponent : public CharacterComponent
	{
		public:
			EnemyCharacterComponent(GameObject& pOwner, const std::string& texFile, const std::string& charName, CharacterType charType, TriangularGrid& grid);
		~EnemyCharacterComponent();
		EnemyCharacterComponent(const EnemyCharacterComponent& other) = delete;
		EnemyCharacterComponent(EnemyCharacterComponent&& other) noexcept = delete;
		EnemyCharacterComponent& operator=(const EnemyCharacterComponent& other) = delete;
		EnemyCharacterComponent& operator=(EnemyCharacterComponent&& other) noexcept = delete;

		void Render() override;
		void Update() override;

		virtual CharacterType GetType() override { return m_Type;  };
		virtual void SetType(CharacterType type) override { m_Type = type; };

		void HandleInput(glm::vec2& input) override;


		void SetTextures();
	private:
		//Enemy specific variables




		//enemy ai movement component

		TricklePathComponent* m_TricklePath;


	};
}

