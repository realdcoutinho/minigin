#include "MovementComponent.h"
#include "GameObject.h"
#include "TimeManager.h"

namespace dae
{
	MovementComponent::MovementComponent(GameObject& pOwner, float speed)
		: BaseComponent(pOwner),
		m_Speed{speed}
	{
		m_pTransform = pOwner.GetComponent<TransformComponent>();
	}

	void MovementComponent::Render()
	{

	}

	void MovementComponent::Update()
	{

	}

	void MovementComponent::Move(glm::vec2& direction)
	{
		auto translation = direction * m_Speed * TimeManager::GetInstance().GetElapsed();
		glm::vec3 newPos = { translation.x + m_pTransform->GetLocalPosition().x, translation.y + m_pTransform->GetLocalPosition().y, 0 };
		m_pTransform->SetPosition(newPos);
	}

	void MovementComponent::MoveToLocation(glm::vec2& location)
	{
		m_pTransform->SetPosition(location);
	}
}