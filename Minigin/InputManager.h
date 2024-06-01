#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Keyboard.h"
#include "Controller.h"


namespace dae
{
	class Input;
	//class Keyboard;
	//class Controller;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		Input& CreateInput();

		void DeleteInput(Input* input);

		Keyboard* GetKeyboard();
		Controller* GetController();

		unsigned int GetControllerIdx() const { return m_ControllerCount; }

	private:
		void Update();
		unsigned int AddController();


		std::vector<std::shared_ptr<Input>> m_Inputs;
		Input* m_ActiveInput;


		std::unique_ptr<Keyboard> m_Keyboard;
		Controller* m_Controller;
		std::vector<std::unique_ptr<Controller>> m_ControllersVector{};
		std::vector<Controller*> m_RawControllersVector{};
		unsigned int m_ControllerCount = 0;

	};

}
