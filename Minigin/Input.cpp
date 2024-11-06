#include "Input.h"

namespace dae
{
	Input::Input()
	{
		m_Keyboard = InputManager::GetInstance().GetKeyboard();
		m_Controller = InputManager::GetInstance().GetController();
	}

	void Input::Process()
	{
		ProcessAxis();
		ProcessActions();
	}


	void Input::AddActionCommand(SDL_Scancode code, SDL_EventType event, std::unique_ptr<Command> command)
	{
		KeyboardKey newKey = std::make_pair(code, event);
		m_KeyboardActionMap[newKey] = std::move(command);
	}

	void Input::AddActionCommand(unsigned int controllerIdx, Controller::ControllerButton button, std::unique_ptr<Command> command)
	{
		ControllerKey newKey = std::make_pair(controllerIdx, button);
		m_ControllerActionMap[newKey] = std::move(command);
	}

	void Input::AddAxisCommand(unsigned int controllerIdx, std::unique_ptr<CommandAxis> command)
	{
		m_ControllerAxisMap[controllerIdx] = std::move(command);
	}

	void Input::AddAxisCommand(std::unique_ptr<CommandAxis> command)
	{
		m_KeyboardAxisVector.emplace_back(std::move(command));
	}

	void Input::RemoveKeyboardCommandsForPlayer(SDL_Scancode scancode)
	{
		std::vector<KeyboardKey> keysToRemove;

		// Find all commands associated with the scancode
		for (const auto& pair : m_KeyboardActionMap)
		{
			if (pair.first.first == scancode)
			{
				keysToRemove.push_back(pair.first);
			}
		}

		// Remove the keys
		for (const auto& key : keysToRemove)
		{
			// Call the destructor of the Command object if needed
			// delete m_KeyboardCommandMap[key]; // Only if you dynamically allocated commands

			m_KeyboardActionMap.erase(key);
		}
	}




	void Input::RemoveControllerCommands(unsigned int controllerIdx)
	{
		auto it = m_ControllerActionMap.begin();
		while (it != m_ControllerActionMap.end())
		{
			if (it->first.first == controllerIdx)
			{
				// Call the destructor of the Command object if needed
				// delete it->second; // Only if you dynamically allocated commands

				it = m_ControllerActionMap.erase(it); // Erase and move to the next
			}
			else
			{
				++it; // Move to the next element
			}
		}

	}

	void Input::ProcessAxis()
	{
		auto dir = m_Controller->GetDPadDirection();

		if (dir != glm::vec2{ 0, 0 })
		{
			for (const auto& command : m_ControllerAxisMap)
			{
				auto co = command.first;
				co;
				command.second->SetDirection(dir);
				command.second->Execute();
			}
			return;
		}
		
		dir = m_Keyboard->GetKeyboardDirection();

		if (dir != glm::vec2{ 0, 0 })
		{
			for (const auto& command : m_KeyboardAxisVector)
			{
				command->SetDirection(dir);
				command->Execute();
			}
			return;

		}

	}

	void Input::ProcessActions()
	{

		for (const auto& command : m_KeyboardActionMap)
		{
			auto button = command.first.first;
			auto eventSDL = command.first.second;
			switch (eventSDL)
			{
			case SDL_KEYDOWN:
				if (m_Keyboard->IsDown(static_cast<unsigned int>(button)))
				{
					//command.second->Execute(button);
					command.second->Execute();
				}
				break;
			case SDL_KEYUP:
				if (m_Keyboard->IsUp(static_cast<unsigned int>(button)))
				{
					//command.second->Execute(button);
					command.second->Execute();
				}
				break;
			case SDL_KEYMAPCHANGED:
				if (m_Keyboard->IsPressed(static_cast<unsigned int>(button)))
				{
					//command.second->Execute(button);
					command.second->Execute();
				}
				break;
			}
		}

		
		for (const auto& pair : m_ControllerActionMap)
		{
			// If you need to access the individual elements of the `ControllerKey` (which is a std::pair itself):
			//unsigned int controllerId = pair.first.first; // Access the unsigned int part of the ControllerKey
			Controller::ControllerButton button = pair.first.second; // Access the ControllerButton part of the ControllerKey
			  

			if (m_Controller->HasStateChange())
			{
				if (m_Controller->IsDown(static_cast<unsigned int>(button)))
						pair.second->Execute();
			}
		}
	}
}
