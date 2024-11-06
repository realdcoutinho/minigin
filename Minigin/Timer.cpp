#include "Timer.h"

#include <algorithm>

using namespace dae;

unsigned int Timer::m_idCounter = 0;

Timer::Timer(const std::string& name) : m_name(name), m_Elapsed(0), m_TotalTime(0)
{

}

Timer::~Timer() = default;

void Timer::Update(float elapsed)
{
	m_Elapsed = elapsed;
	m_TotalTime += m_Elapsed;
	m_name;
}

