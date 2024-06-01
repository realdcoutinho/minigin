#include "Scene.h"
#include "GameObject.h"
#include "TimeManager.h"
#include "InputManager.h"
#include <algorithm>
#include "Observer.h"


using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) 
	: m_name(name) 
	, m_pTimer(TimeManager::GetInstance().CreateTimer(name))
	, m_pInput(InputManager::GetInstance().CreateInput())
{
	//m_pPlayerDeathObserver = std::make_shared<PlayerDeathObserver>(this);
}

void dae::Scene::RemoveInactiveObjects()
{
	m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(),
		[](const std::unique_ptr<GameObject>& object) { return !object->IsActive(); }),
		m_objects.end());
}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(GameObject* object)
{
	//object;
	//m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());

	object;

	//auto newEnd = std::remove_if(m_objects.begin(), m_objects.end(),
	//	[object](const std::unique_ptr<GameObject>& ptr) {
	//		return ptr.get() == object; // Compare raw pointers
	//	});

	// Actually remove the elements from the vector
	//m_objects.erase(newEnd, m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for (auto& obj : m_objects) 
	{
		if (obj->IsActive()) {
			obj->Update();
		}
	}
}

void dae::Scene::FixedUpdate()
{
	RemoveInactiveObjects();
}

void Scene::Render() const
{
	for (const auto& obj : m_objects) 
	{
		if (obj->IsActive()) {
			obj->Render();
		}
	}
}

Timer& Scene::GetTimer() const
{
	return m_pTimer;
}

Input& Scene::GetSceneInput() const
{
	return m_pInput;
}