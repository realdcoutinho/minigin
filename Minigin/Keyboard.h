#pragma once
#include <SDL.h>
#include <vector>
#include <glm/glm.hpp>


namespace dae
{


	class Keyboard final
	{
	public:

		Keyboard();
		~Keyboard();

		void Update();

		bool IsDown(int keyNumber) const;
		bool IsUp(int keyNumber) const;
		bool IsPressed(int keyNumber) const;

		glm::vec2 GetKeyboardDirection() const;
		//bool GetState() const { return m_HasStateChanged; }
	private:

		bool m_PreviousState[256]{}; // 256 is the number of keys on a keyboard
		bool m_CurrentState[256]{}; // 256 is the number of keys on a keyboard
	
	};


}
