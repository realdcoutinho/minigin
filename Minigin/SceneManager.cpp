#include "SceneManager.h"
//#include "TimeManager.h
#include "Scene.h"
#include "SDL.h"
#include <iostream>



dae::SceneManager::~SceneManager() = default;

void dae::SceneManager::SetActiveTimer()
{
	TimeManager::GetInstance().SetActiveTimer(m_pActiveScene->GetTimer());
}


void dae::SceneManager::Update()
{
	if(m_pActiveScene)
		m_pActiveScene->Update();
	//for(auto& scene : m_scenes)
	//{
	//	scene->Update();
	//}
}

void dae::SceneManager::Render()
{
	//for (const auto& scene : m_scenes)
	//{
	//	scene->Render();
	//}

	if (m_pActiveScene)
		m_pActiveScene->Render();
}

void dae::SceneManager::FixedUpdate() 
{
	if (m_pActiveScene) 
	{
		m_pActiveScene->FixedUpdate();
	}
}


dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	//const auto& scene = std::make_unique<Scene>(name);
	//const auto& sceneGet = scene.get();
	//m_scenes.push_back(std::move(scene));
	//return *sceneGet;

	const auto& scene = std::make_shared<Scene>(name);
	m_scenes.push_back(scene);
	return *scene;


}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	for (const auto& scene : m_scenes)
	{
		if (scene->GetSceneName() == name)
		{
			m_pActiveScene = scene.get();

			//return;
		}
	}

	TimeManager::GetInstance().SetActiveTimer(m_pActiveScene->GetTimer());
}

void dae::SceneManager::SetActiveScene(const Scene& scene)
{
	m_pActiveScene = const_cast<Scene*>(&scene);
	TimeManager::GetInstance().SetActiveTimer(m_pActiveScene->GetTimer());
}

void dae::SceneManager::SwitchScene()
{
	if (m_scenes.empty()) 
	{
		m_pActiveScene = nullptr;
		return;
	}

	if (m_pActiveScene == nullptr) 
	{
		// If there is no active scene, start with the first scene
		m_pActiveScene = m_scenes.front().get();
	}
	else 
	{
		// Find the next scene in the vector
		bool found = false;
		for (size_t i = 0; i < m_scenes.size(); ++i) 
		{
			if (m_pActiveScene == m_scenes[i].get()) 
			{
				if (i + 1 < m_scenes.size()) 
				{
					m_pActiveScene = m_scenes[i + 1].get();
					TimeManager::GetInstance().SetActiveTimer(m_pActiveScene->GetTimer());

				}
				else 
				{
					// If it's the last scene, wrap around to the first scene
					m_pActiveScene = m_scenes.front().get();
					TimeManager::GetInstance().SetActiveTimer(m_pActiveScene->GetTimer());
				}
				found = true;
				break;
			}
		}

		// If the current scene wasn't found (perhaps it was deleted), default to the first scene
		if (!found) {
			m_pActiveScene = m_scenes.front().get();
			TimeManager::GetInstance().SetActiveTimer(m_pActiveScene->GetTimer());
		}
	}
}

dae::Scene& dae::SceneManager::GetActiveScene() const
{
	return *m_pActiveScene;
}

dae::Scene& dae::SceneManager::GetSceneByName(const std::string& name) const
{
	for (const auto& scene : m_scenes)
	{
		if (scene->GetSceneName() == name)
		{
			return *scene;
		}
	}
	throw std::exception("Scene not found");
}
