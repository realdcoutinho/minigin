#include "TransformComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <iostream>

dae::TransformComponent::TransformComponent(GameObject& pOwner)
	: BaseComponent(pOwner),
	m_LocalPosition(0, 0, 0),
	m_WorldPosition{ 0, 0, 0 }
{
}


void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	m_IsDirty = true;
}
void dae::TransformComponent::SetPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
	m_IsDirty = true;
}

void dae::TransformComponent::SetPosition(const glm::vec2& position)
{
	m_LocalPosition = { position.x, position.y, 0 };
	m_IsDirty = true;
}

glm::vec3& dae::TransformComponent::GetWorldPosition()
{
	if (m_IsDirty)
	 {

		UpdateWorldPosition();

	 }
	 return m_WorldPosition;	
}

 void dae::TransformComponent::UpdateWorldPosition()
 {

		 auto test = GetOwner();
		 if (test->GetParent() != nullptr)
		 {

			 m_WorldPosition = GetOwner()->GetParent()->GetWorldPosition() + m_LocalPosition;
			 m_IsDirty = false;
		 }
		 else
		 {
			 m_LocalPosition = GetOwner()->GetLocalPosition();
			 m_IsDirty = false;
			 m_WorldPosition = m_LocalPosition;
		 }
 }

 glm::vec3& dae::TransformComponent::GetLocalPosition()
 {
	 return m_LocalPosition;
 }

void dae::TransformComponent::Render()
{

}

void dae::TransformComponent::Update()
{

}