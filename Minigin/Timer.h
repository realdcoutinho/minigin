#pragma once
#include "TimeManager.h"
#include <memory>
#include <string>

namespace dae
{
	class Timer
	{
		friend Timer& TimeManager::CreateTimer(const std::string& name);
	public:

		void Update(float elapsed);

		~Timer();
		Timer(const Timer& other) = delete;
		Timer(Timer&& other) = delete;
		Timer& operator=(const Timer& other) = delete;
		Timer& operator=(Timer&& other) = delete;

		float GetElapsed() const { return m_Elapsed; }
		float GetTotalTime() const { return m_TotalTime; }
		std::string& GetSceneName() { return m_name; }
		//cannot be private
		/*explicit*/ Timer(const std::string& name);

	private:
		/*explicit*/

		std::string m_name;
		float m_Elapsed;
		float m_TotalTime;
		static unsigned int m_idCounter;
	};

}

