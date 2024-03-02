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


	class GameObject final: public std::enable_shared_from_this<GameObject>
	{
	public:

		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		virtual void Update(float elasped);
		virtual void Render() const;
		//void SetTexture(const std::string& filename);
		
		//TRANSFORM
		void SetLocalPosition(float x, float y);
		void SetLocalPosition(const glm::vec3& pos);
		glm::vec3& GetWorldPosition();
		glm::vec3& GetLocalPosition();

		void InitializeTransformComponent();
		TransformComponent* GetTransformComponent() { return m_pTransformComponent; }
		void RemoveComponent(BaseComponent* pComponent/*, bool deleteObject = false*/);
		void SetParent(const std::shared_ptr<GameObject>& newParent, bool keepWorldPosition = false);
					
		GameObject* GetParent() const { return m_parent.lock().get(); }



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



		template<typename T>
		std::enable_if_t<std::is_base_of_v<BaseComponent, T>, T*>
		AddComponent(T* pComp)
		{
			if (!HasComponent<T>())
			{
				std::unique_ptr<T> pNewComp(pComp);
				m_pComponents.push_back(std::move(pNewComp));

				return pComp;
			}

			return nullptr;
		}

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

	private:
		//Diogos
		bool IsDescendantOf(const std::shared_ptr<GameObject>& potentialAncestor) const;

		std::vector<std::unique_ptr<BaseComponent>> m_pComponents;
		TransformComponent* m_pTransformComponent;
		std::weak_ptr<GameObject> m_parent{};
		std::vector<std::shared_ptr<GameObject>> m_Children{};
	
		glm::vec3 m_LocalPosition;
	};

}