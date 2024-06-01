#include "BaseComponent.h" // Include the BaseComponent header
#include <glm/glm.hpp>
#include <memory>


#pragma once
namespace dae
{

	class TransformComponent : public BaseComponent
	{
	public:
		TransformComponent(GameObject&  pOwner);

		~TransformComponent() override = default;

		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		void SetDirty() { m_IsDirty = true; }

		void Render() override;
		void Update() override;

		void SetPosition(float x, float y, float z);
		void SetPosition(const glm::vec3& position);
		void SetPosition(const glm::vec2& position);

		glm::vec3& GetLocalPosition();
		glm::vec3& GetWorldPosition();

		bool IsDirty() const { return m_IsDirty; }

		//void Translate(float x, float y, float z);
		//void Translate(const glm::vec3& position);
		//void Translate(const XMVECTOR& position);
		//
		//void Rotate(float x, float y, float z, bool degrees = true);
		//void Rotate(const glm::vec3& rotation, bool degrees = true);
		//void Rotate(const XMVECTOR& rotation, bool isQuaternion = true);
		//
		//void Scale(float x, float y, float z);
		//void Scale(float s);
		//void Scale(const XMFLOAT3& scale);
		//
		//
		//glm::vec3& GetScale()  { return m_Scale; }
		//glm::vec3& GetWorldScale()  { return m_WorldScale; }
		//glm::vec4& GetRotation()  { return m_Rotation; }
		//glm::vec4& GetWorldRotation()  { return m_WorldRotation; }
		//glm::mat4& GetWorld()  { return m_World; }
		//
		//glm::vec3& GetForward()  { return m_Forward; }
		//glm::vec3& GetUp()  { return m_Up; }
		//glm::vec3& GetRight()  { return m_Right; }
		//
		//
		//void SetRigidBodyComponent(RigidBodyComponent* pRigidBody) { m_pRigidBodyComponent = pRigidBody; }
		//void SetControllerComponent(ControllerComponent* pController) { m_pControllerComponent = pController; }

	protected:
		bool m_IsDirty{};
		void UpdateWorldPosition();

		//void Initialize(const SceneContext& sceneContext) override;
		//void Update(const SceneContext& sceneContext) override;
		//
		//void UpdateTransforms();
		//bool CheckConstraints() const;
		//
		//bool CheckIfDirty();

	private:

		glm::vec3 m_LocalPosition{}, m_WorldPosition{};

		//glm::vec3 m_Scale{}, m_WorldScale{};
		//glm::vec3 m_Forward{}, m_Up{}, m_Right{};
		//glm::vec4 m_Rotation{}, m_WorldRotation{};
		//glm::mat4 m_World{};
		//
		//
		//
		//
		//TransformChanged m_IsTransformChanged{};
		//
		//RigidBodyComponent* m_pRigidBodyComponent{};
		//ControllerComponent* m_pControllerComponent{};
	};
}

