#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include <glm/glm.hpp>

namespace dae
{
	class MovementComponent : public BaseComponent
	{
	public:
		MovementComponent(GameObject& pOwner, float speed);

		void Render() override;
		void Update() override;

		void Move(glm::vec2& direction);

		void MoveToLocation(glm::vec2& location);
	private:

		TransformComponent* m_pTransform{};
		float m_Speed;
	};

}

