#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Timer.h"

void dae::TimeManager::Update(float elapsed)
{
	m_ActiveTimer->Update(elapsed);
	m_GlobalElapsed = elapsed;
}

dae::Timer& dae::TimeManager::CreateTimer(const std::string& sceneName)
{
	std::shared_ptr<Timer> timer = std::make_shared<Timer>(sceneName);
	m_Timers.push_back(timer);
	return *timer.get();
}

dae::Timer& dae::TimeManager::GetTimer()
{
	auto& scene = SceneManager::GetInstance().GetActiveScene();
	auto& timer = scene.GetTimer();
	return timer;
}

float dae::TimeManager::GetElapsed() const
{
	auto& scene = SceneManager::GetInstance().GetActiveScene();
	auto& timer = scene.GetTimer();
	return timer.GetElapsed();
}

float dae::TimeManager::GetTotalTime() const
{
	auto& scene = SceneManager::GetInstance().GetActiveScene();
	auto& timer = scene.GetTimer();
	return timer.GetTotalTime();
}

float dae::TimeManager::GlobalElapsed() const
{
	return m_GlobalElapsed;
}
