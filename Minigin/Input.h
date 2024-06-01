#pragma once
#include <map>
#include "SDL.h"
#include <vector>
#include <memory>
#include "../QBert/GameCommand.h"
#include "Keyboard.h"
#include "Controller.h"
#include "InputManager.h"


namespace dae
{
	class Command;

	class Input final
	{
		friend Input& InputManager::CreateInput();
	public:
		Input();

		void Process();

		void AddActionCommand(SDL_Scancode code, SDL_EventType event, std::unique_ptr<Command> command);
		void AddActionCommand(unsigned int controllerIdx, Controller::ControllerButton button, std::unique_ptr<Command> command);

		void RemoveControllerCommands(unsigned int controllerIdx);
		void RemoveKeyboardCommandsForPlayer(SDL_Scancode scancode);


		void AddAxisCommand(unsigned int controllerIdx, std::unique_ptr<CommandAxis> command);
		void AddAxisCommand(std::unique_ptr<CommandAxis> command);

	private:

		void ProcessActions();
		void ProcessAxis();
		

		//Action Mappings
		using KeyboardKey = std::pair <SDL_Scancode, SDL_EventType>;
		using KeyboardActionMap = std::map<KeyboardKey, std::unique_ptr<Command>>;

		using ControllerKey = std::pair <unsigned int, Controller::ControllerButton>;
		using ControllerActionMap = std::map<ControllerKey, std::unique_ptr<Command>>;

		KeyboardActionMap m_KeyboardActionMap{};
		ControllerActionMap m_ControllerActionMap{};


		//AXIS MAPPINGS
		using ControllerAxisMap = std::map<unsigned int, std::unique_ptr<CommandAxis>>;
		ControllerAxisMap m_ControllerAxisMap{};
		std::vector<std::unique_ptr<CommandAxis>> m_KeyboardAxisVector;


		Keyboard* m_Keyboard;
		Controller* m_Controller;
		//std::vector<Controller*> m_ControllersVector{};
	};

}

