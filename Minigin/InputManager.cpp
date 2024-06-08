#include <SDL.h>
#include "InputManager.h"
#include <backends/imgui_impl_sdl2.h>

#include "SceneManager.h"
#include "Scene.h"
#include "Input.h"
//#include "Keyboard.h"
//#include "Controller.h"

#include <iostream>

bool dae::InputManager::ProcessInput()
{

	auto& sc  = SceneManager::GetInstance().GetActiveScene();
	auto& input = sc.GetSceneInput();
	input.Process();
	Update();

	bool running = true;

	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT) {
			running = false;
		}
		if (e.type == SDL_KEYDOWN) 
		{

			if (e.key.keysym.scancode == SDL_SCANCODE_F5)
			{
				SceneManager::GetInstance().SwitchScene();
			}
			//if (e.button == SDL_SCANCODE_F5)
			//{
			//	SceneManager::GetInstance().SwitchScene();
			//}
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}


		// etc...
		ImGui_ImplSDL2_ProcessEvent(&e);
	}


	
	return running;
}

void dae::InputManager::Update()
{
	m_Keyboard->Update();


	//m_ControllersVector[0]->Update();
	std::for_each(m_ControllersVector.begin(), m_ControllersVector.end(), [](const std::unique_ptr<Controller>& controllerPtr) 
		{
			controllerPtr->Update();
		});

}

dae::Input& dae::InputManager::CreateInput()
{
	std::shared_ptr<Input> input = std::make_shared<Input>();
	m_Inputs.push_back(input);
	return *input.get();
}

dae::Keyboard* dae::InputManager::GetKeyboard()
{
	if (m_Keyboard == nullptr)
	{
		m_Keyboard = std::make_unique<Keyboard>();
	}
	return m_Keyboard.get();
}

dae::Controller* dae::InputManager::GetController()
{
	if (m_Controller == nullptr)
	{
		m_Controller = m_ControllersVector[AddController()].get();
		return m_Controller;
	}
	return m_ControllersVector[m_ControllerCount - 1].get();
}

//std::vector<dae::Controller*>& dae::InputManager::GetControllers()
//{
//
//
//	//static std::vector<std::unique_ptr<int>> uniquePtrVec;
//
//
//	//if (m_ControllersVector.empty())
//	//{
//	//	AddController();
//	//}
//
//	m_RawControllersVector.reserve(m_ControllersVector.size()); // Preallocate memory for efficiency
//
//	// Use std::transform to convert unique_ptr to raw pointers
//	std::transform(m_ControllersVector.begin(), m_ControllersVector.end(), std::back_inserter(m_RawControllersVector),
//		[](const std::unique_ptr<dae::Controller>& uniquePtr) -> dae::Controller* {
//			return uniquePtr.get(); // .get() returns the raw pointer
//		});
//
//	return m_RawControllersVector;
//
//	//return &m_ControllersVector;
//}

unsigned int dae::InputManager::AddController()
{
	auto controller = std::make_unique<Controller>(m_ControllerCount);
	m_ControllersVector.push_back(std::move(controller));
	unsigned int currentIdx = m_ControllerCount;
	m_ControllerCount++;
	return currentIdx;
}

void dae::InputManager::DeleteInput(Input* input)
{
	auto it = std::find_if(m_Inputs.begin(), m_Inputs.end(), [input](std::shared_ptr<Input> p) {return p.get() == input; });
	if (it != m_Inputs.end()) 
	{
		m_Inputs.erase(it);
	}
}
