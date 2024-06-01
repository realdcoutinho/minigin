#include <windows.h>
#include "KeyBoard.h"
#include <algorithm> 
#include <SDL.h>

namespace dae 
{
	Keyboard::Keyboard()
	{
		ZeroMemory(&m_PreviousState, sizeof(bool) * 256);
		ZeroMemory(&m_CurrentState, sizeof(bool) * 256);
	}

	Keyboard::~Keyboard()
	{

	}

	bool Keyboard::IsDown(int keyNumber) const
	{
		return m_CurrentState[keyNumber] && !m_PreviousState[keyNumber];

	}

	bool Keyboard::IsUp(int keyNumber) const
	{
		return !m_CurrentState[keyNumber] && m_PreviousState[keyNumber];
	}

	bool Keyboard::IsPressed(int keyNumber) const
	{
		return m_CurrentState[keyNumber];

	}

	void Keyboard::Update()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(bool) * 256);
		ZeroMemory(&m_CurrentState, sizeof(bool) * 256);

		const Uint8* state = SDL_GetKeyboardState(NULL);
		for (size_t i = 0; i < 256; ++i)
		{
			m_CurrentState[i] = state[i];
		}
	}

	glm::vec2 Keyboard::GetKeyboardDirection() const
	{
		glm::vec2 axis{};
		if (IsDown(SDL_SCANCODE_A)) axis.x = -1.f;
		else if (IsDown(SDL_SCANCODE_D)) axis.x = 1.0f;

		if (IsDown(SDL_SCANCODE_S)) axis.y = 1.f;
		else if (IsDown(SDL_SCANCODE_W)) axis.y = -1.0f;

		return axis;
	}
	
}
