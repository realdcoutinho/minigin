#include "RotatorComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "TimeManager.h"

dae::RotatorComponent::RotatorComponent(GameObject& pOwner, float radius, float speed)
	: BaseComponent(pOwner)
	, m_Radius(radius)
	, m_RotSpeed(speed)
{
	m_pTransform = pOwner.GetComponent<TransformComponent>();
	m_Center = m_pTransform->GetLocalPosition();
}

void dae::RotatorComponent::Render()
{

}

void dae::RotatorComponent::Update()
{
	float elapsed = TimeManager::GetInstance().GetElapsed();


	if (m_pTransform == nullptr)
		return;

	m_CurRadians += m_RotSpeed * elapsed;

	float posX =  cosf(m_CurRadians) * m_Radius;
	float posY =  sinf(m_CurRadians) * m_Radius;

	glm::vec3 newPos{ posX + m_Center.x, posY + m_Center.y, 0 };

	m_pTransform->SetPosition(newPos);
}