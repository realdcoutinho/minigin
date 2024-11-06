#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace dae
{
	class Timer;
	class TimeManager final : public Singleton<TimeManager>
	{
	public:
		Timer& CreateTimer(const std::string& name);

		Timer& GetTimer();
		float GetElapsed() const;
		float GetTotalTime() const;

		float GlobalElapsed() const;

		void Update(float elapsed);

		void SetActiveTimer(const Timer& timer) { m_ActiveTimer = const_cast<Timer*>(&timer); }

	private:
		friend class Singleton<TimeManager>;
		TimeManager() = default;
		std::vector<std::shared_ptr<Timer>> m_Timers;
		Timer* m_ActiveTimer;
		float m_GlobalElapsed{ 0.0f };
	};
}

