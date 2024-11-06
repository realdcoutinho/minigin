#pragma once
#include "BaseComponent.h"
#include "CharacterComponent.h"


namespace dae
{
	class GridNavigator;
	class HealthComponent;
	class ScoreComponent;
	class QBertCharacterComponent : public CharacterComponent
	{
	public:
		QBertCharacterComponent(GameObject& pOwner, TriangularGrid& pGrid);
		~QBertCharacterComponent();
		QBertCharacterComponent(const QBertCharacterComponent& other) = delete;
		QBertCharacterComponent(QBertCharacterComponent&& other) noexcept = delete;
		QBertCharacterComponent& operator=(const QBertCharacterComponent& other) = delete;
		QBertCharacterComponent& operator=(QBertCharacterComponent&& other) noexcept = delete;
		void Render() override;
		void Update() override;

		int GetHealthValue() const;
		int GetScoreValue() const;

		virtual CharacterType GetType() override { return m_Type; };
		virtual void SetType(CharacterType type) override { m_Type = type; };

		void HandleInput(glm::vec2& input) override;

	private:
		ScoreComponent* m_Score;
		HealthComponent* m_Health;
		GridNavigator* m_Navigator;
	};
}


