#pragma once
#include <memory>
#include "Transform.h"
#include <string>
#include <algorithm> // for std::copy_if
#include <iterator>  // for std::back_inserter
#include <typeinfo>  // for typeid
#include <vector>
#include <memory>
#include <unordered_map>
#include <typeindex>
#include "TransformComponent.h"

namespace dae
{
	class Texture2D;
	class BaseComponent;


	class GameObject final/*: public std::enable_shared_from_this<GameObject>*/
	{
	public:

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		virtual void Update();
		virtual void Render() const;
		//void SetTexture(const std::string& filename);
		
		//TRANSFORM
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalPosition(const glm::vec2& pos);
		glm::vec3& GetWorldPosition();
		glm::vec3& GetLocalPosition();

		void InitializeTransformComponent();
		TransformComponent* GetTransformComponent() { return m_pTransformComponent; }
		void RemoveComponent(BaseComponent* pComponent/*, bool deleteObject = false*/);
		void SetParent(/*const std::shared_ptr<GameObject>& */ GameObject* newParent, bool keepWorldPosition = false);
					
		GameObject* GetParent() const { return m_parent/*.lock().get()*/; }

		bool IsDirty() { return m_pTransformComponent->IsDirty(); };

		////Diogo 
		template<typename T>
		std::enable_if_t<std::is_base_of_v<BaseComponent, T>, std::unique_ptr<T>>
		AddComponent(std::unique_ptr<T> pComp)
		{
			if (!HasComponent<T>())
			{
				m_pComponents.push_back(std::move(pComp));

				return std::move(pComp);
			}

			return nullptr;
		}



		//template<typename T>
		//std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*>
		//AddComponent(T* pComp)
		//{
		//	if (!HasComponent<T>())
		//	{
		//		std::unique_ptr<T> pNewComp(pComp);
		//		m_pComponents.push_back(std::move(pNewComp));

		//		//m_pComponentsR.push_back(pComp);

		//		return pComp;
		//	}

		//	return nullptr;
		//}

		template <class T>
		T* GetComponent(/*bool searchChildren = false*/)
		{
			auto it = std::find_if(m_pComponents.begin(), m_pComponents.end(), [](const std::unique_ptr<dae::BaseComponent>& component) {
				return component && typeid(*component) == typeid(T);
				});


			 if (it != m_pComponents.end()) 
			 {
				 return dynamic_cast<T*>(it->get());
			 }

			return nullptr;
		}

		template <class T>
		bool HasComponent(/*bool searchChildren = false*/)
		{
			return GetComponent<std::unique_ptr<T>>(/*searchChildren*/) != nullptr;
		}

		unsigned int GetID() const { return m_ID; }


		void SetActive(bool active);
		void SetDestroy() { m_SetDestroy = true; }
		bool IsActive() const;

	private:
		//Diogos
		bool IsDescendantOf(const GameObject& potentialAncestor) const;
		bool m_IsActive = true;
		bool m_SetDestroy = false;

		std::vector<std::unique_ptr<BaseComponent>> m_pComponents;
		TransformComponent* m_pTransformComponent;
		GameObject* m_parent{};
		std::vector<GameObject*> m_Children{};
		glm::vec3 m_LocalPosition;

		//unsigned int m_ID;             // Unique identifier for the GameObject
		static unsigned int m_NextID;  // Static variable to track the next available ID

		unsigned int m_ID;  // Static member variable to track the number of instances

	};




}

