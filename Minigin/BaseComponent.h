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
		//virtual void SetGameObject(GameObject* pGameObject) = 0;
		//virtual GameObject* GetGameObject() = 0;

		//GameObject* GetGameObject() const { return m_pGameObject; }
		Scene* GetScene() const { return m_pScene; }
		
		void SetOwner(GameObject* pOwner);


	protected:

		explicit BaseComponent(std::shared_ptr<GameObject> pOwner);
		explicit BaseComponent(GameObject* pOwner);
		explicit BaseComponent() {};
		GameObject* GetOwner() const { return m_pOwner; }


		Scene* m_pScene{};

		bool m_IsInitialized{};
		int m_ComponentId{ 0 };
		GameObject* m_pOwner{};
	private:
	
		static unsigned int m_idCounter;

	};
}
