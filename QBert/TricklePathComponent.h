#pragma once
#include "BaseComponent.h"
#include <glm/vec2.hpp>

namespace dae
{
	struct DownVectors
	{
		glm::vec2 DownLeft = { 1, 0 };
		glm::vec2 DownRight = { 0, -1 };
	};

	struct LeftVectors
	{
		glm::vec2 LeftUp = { -1, 0 };
		glm::vec2 LeftDown = { 0, -1 };
	};

	struct RightVectors
	{
		glm::vec2 RightUp = { 0, 1 };
		glm::vec2 RightDown = { 1, 0 };
	};

	enum class TrickleType
	{
		Left,
		Right,
		Down
	};

	class GridNavigator;
	class GameObject;

	class TricklePathComponent : public BaseComponent
	{
	public:
		TricklePathComponent(GameObject& pOwner, TrickleType type);
		~TricklePathComponent();
		TricklePathComponent(const TricklePathComponent&) = delete;
		TricklePathComponent(TricklePathComponent&&) = delete;
		TricklePathComponent& operator= (const TricklePathComponent&) = delete;
		TricklePathComponent& operator= (const TricklePathComponent&&) = delete;

		virtual void Render() override {};
		virtual void Update() override;
		void Stop() { m_IsDead = true; }

	private:

		glm::vec2 TricklePath();
		void MovementUpdate();

		
		TrickleType m_Type;

		bool m_IsDead = false;
		float m_MoveTimer = 0.0f;
		const float m_MoveTime = 0.9f;
		bool m_CanMove = false;
	};
}

