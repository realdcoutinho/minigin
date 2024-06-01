#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class GameObject;
	class CharacterComponent;
	class ScoreComponent;
	class HealthComponent;
	class TriangularGrid;
	class RespawnComponent;
	class QBertComponent final : public BaseComponent
	{
	public:
		QBertComponent(GameObject& pOwner, TriangularGrid& pGrid, int startingNode, int player = 1);
		~QBertComponent();
		QBertComponent(const QBertComponent& other) = delete;
		QBertComponent(QBertComponent&& other) noexcept = delete;
		QBertComponent& operator=(const QBertComponent& other) = delete;
		QBertComponent& operator=(QBertComponent&& other) noexcept = delete;
		void Render() override;
		void Update() override;

		int GetHealthValue() const;
		int GetScoreValue() const;

	private:
		CharacterComponent* m_Character;
		ScoreComponent* m_Score;
		HealthComponent* m_Health;
		RespawnComponent* m_Respawn;
		const std::string m_QBertTextureFile1{ "Qbert P1 Spritesheet.png" };
		const std::string m_QBertTextureFile2{ "Qbert P2 Spritesheet.png" };

	};
}


