#pragma once
#include "SceneManager.h"
#include "GameObject.h"
#include <memory>
#include "Timer.h"
//#include "Input.h"

namespace dae
{
	//class GameObject;
	class Timer;
	class Input;
	class PlayerDeathObserver;
	class Scene final
	{
		friend Scene&  SceneManager::CreateScene(const std::string& name);
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(GameObject* object);
		void RemoveAll();

		void Update();
		void FixedUpdate();
		void Render() const;

		const std::string& GetSceneName() const { return m_name; }
		Timer& GetTimer() const; 
		Input& GetSceneInput() const; 

		~Scene();
		Scene(const std::string& name);

	private: 

		std::string m_name;
		Timer& m_pTimer;
		Input& m_pInput;

		std::vector<std::unique_ptr<GameObject>> m_objects{};

		void RemoveInactiveObjects();


		static unsigned int m_idCounter; 
	};

}
