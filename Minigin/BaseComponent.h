#pragma once
#include <memory>

namespace dae 
{

	class GameObject;
	class Scene;

	class BaseComponent
	{
	public:

		virtual ~BaseComponent() = default;
		virtual void Update() = 0;
		virtual void Render() = 0;

		virtual void SetActive(bool active) { m_IsActive = active; }
		bool IsActive() const { return m_IsActive; }

		unsigned int GetOwnerID() const;
		GameObject* GetOwner() const { return m_pOwner; }

	protected:

		explicit BaseComponent(std::unique_ptr<GameObject> pOwner);
		explicit BaseComponent(GameObject& pOwner);
		explicit BaseComponent() {};




		bool m_IsInitialized{};
		int m_ComponentId{ 0 };

	private:
		bool m_IsActive{ true };


		void SetOwner(GameObject* pOwner);
		GameObject* m_pOwner{};
		static unsigned int m_idCounter;

	};
}
