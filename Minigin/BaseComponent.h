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
		virtual void Update(float elapsed) = 0;
		virtual void Draw() {};
		virtual void Render() const = 0;

	protected:

		explicit BaseComponent(std::shared_ptr<GameObject> pOwner);
		explicit BaseComponent(GameObject* pOwner);
		explicit BaseComponent() {};
		GameObject* GetOwner() const { return m_pOwner; }


		bool m_IsInitialized{};
		int m_ComponentId{ 0 };

	private:
	
		void SetOwner(GameObject* pOwner);
		GameObject* m_pOwner{};
		static unsigned int m_idCounter;

	};
}
