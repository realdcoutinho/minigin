#include "TransformComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include <iostream>


dae::TransformComponent::TransformComponent(std::shared_ptr<GameObject>  pOwner) 
	: BaseComponent(pOwner),
	m_LocalPosition( 0, 0, 0 ),
	m_WorldPosition{ 0, 0, 0 },
	m_Scale{ 1, 1, 1 },
	m_WorldScale{ 1, 1, 1 },
	m_Forward{ 0, 0, 1 },
	m_Up{ 0, 1, 0 },
	m_Right{ 1, 0, 0 },
	m_Rotation{ 0, 0, 0, 1 },
	m_WorldRotation{ 0, 0, 0, 1 }
{
	std::cout << "transformComponent created\n";
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_LocalPosition.x = x;
	m_LocalPosition.y = y;
	m_LocalPosition.z = z;
	m_IsDirty = true;
	//GetWorldPosition();
}
void dae::TransformComponent::SetPosition(const glm::vec3& position)
{
	m_LocalPosition = position;
	m_IsDirty = true;
	//GetWorldPosition();
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
	 if (m_IsDirty)
	 {
		 auto test = GetOwner();
		 if (test->GetParent() != nullptr)
		 {

			 m_WorldPosition = GetOwner()->GetParent()->GetWorldPosition() + GetOwner()->GetLocalPosition();
			 m_IsDirty = false;
		 }
		 else
		 {
			 m_LocalPosition = GetOwner()->GetLocalPosition();
			 m_IsDirty = false;

			 m_WorldPosition = m_LocalPosition;
		 }
	 }
	 //m_IsDirty = false;
 }

 glm::vec3& dae::TransformComponent::GetLocalPosition()
 {
	 return m_LocalPosition;
 }


//dae::TransformComponent::TransformComponent(GameObject* pOwner)
//: BaseComponent()//,
//{
//	pOwner;
//	std::cout << "transformComponent created\n";
//}

void dae::TransformComponent::Render() const
{
	//if (m_TextTexture != nullptr)
	//{
	//	//const auto& pos = m_Transform.GetPosition();
	//	Renderer::GetInstance().RenderTexture(*m_TextTexture, m_Positon.x, m_Positon.y);
	//}
}

void dae::TransformComponent::Update(float elasped)
{
	elasped;
	//TextComponent::Update(elasped);

	///// Update the queue of frame times
	//if (m_FrameRateVector.size() >= m_MaxFrameSamples)
	//{
	//	m_FrameRateVector.erase(m_FrameRateVector.begin()); // Remove the oldest frame time
	//}
	//m_FrameRateVector.emplace_back(elasped); // Add the new frame time

	//m_AccumulatedTime += elasped;

	//// Update the FPS display every 0.15 seconds
	//if (m_AccumulatedTime > 0.15f)
	//{
	//	// Calculate the average frame time
	//	float sum = std::accumulate(m_FrameRateVector.begin(), m_FrameRateVector.end(), 0.0f);
	//	float averageFrameTime = sum / m_FrameRateVector.size();

	//	// Compute FPS from the average frame time
	//	float averageFPS = 1.0f / averageFrameTime;

	//	// Format and set the FPS text
	//	std::stringstream stream;
	//	stream << std::fixed << std::setprecision(1) << averageFPS;
	//	std::string fpsText = stream.str() + " FPS";
	//	SetText(fpsText);

	//	m_AccumulatedTime = 0.0f;
	//}
}