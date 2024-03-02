#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::RotatorComponent::RotatorComponent(std::shared_ptr<GameObject> pOwner, float radius, float speed)
	: BaseComponent(pOwner)
	, m_Radius(radius)
	, m_RotSpeed(speed)
{
	m_pTransform = pOwner->GetComponent<TransformComponent>();
	m_Center = m_pTransform->GetLocalPosition();
}

dae::RotatorComponent::RotatorComponent(GameObject* pOwner, float radius, float speed)
	: BaseComponent(pOwner)
	, m_Radius(radius)
	, m_RotSpeed(speed)
{
	m_pTransform = pOwner->GetComponent<TransformComponent>();
	m_Center = m_pTransform->GetLocalPosition();

}

void dae::RotatorComponent::Render() const
{

}

void dae::RotatorComponent::Update(float elapsed)
{
	if (!m_pTransform)
	{
		//todo: Place warning later. Ask teacher whether I can already implement
		return;
	}
	m_CurrentRadians += m_RotSpeed * elapsed;

	const float newYPosRot{ sinf(m_CurrentRadians) * m_Radius };
	const float newXPosRot{ cosf(m_CurrentRadians) * m_Radius };

	glm::vec3 newPos{ newXPosRot + m_Center.x, newYPosRot + m_Center.y, 0 };

	m_pTransform->SetPosition(newPos);
}