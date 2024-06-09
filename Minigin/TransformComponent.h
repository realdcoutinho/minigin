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


	protected:
		bool m_IsDirty{};
		void UpdateWorldPosition();

	private:
		glm::vec3 m_LocalPosition{}, m_WorldPosition{};
	};
}

