#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TimeManager.h"
#include <thread>
#include <chrono>
#include <AudioSystem.h>
#include <ServiceLocator.h>
#include "GameModeManager.h"

#include "EventDispatcher.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version);
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version);
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

dae::Minigin::Minigin(const std::string &dataPath)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640, //640
		480, //480
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);
}

dae::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run(/*const std::function<void()>& load*/)
{

	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();
	auto& timeManager = TimeManager::GetInstance();
	auto& gameModeManager = GameModeManager::GetInstance();


	//auto& eventManager = EventManager::GetInstance();
	auto& eventDispatcher = EventDispatcher::GetInstance();


	// todo: this update loop could use some work.
	bool doContinue = true;
	auto last_time = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;
	//const float fixed_time_step = 1.0f / 60.0f;


	float desiredFrameRate{ 144.0f };
	int msPerFrame = static_cast<int>(1000 / desiredFrameRate); // Milliseconds per frame for 144 FPS

	//eventManager.Initialize();
	eventDispatcher.Initialize();

	while (doContinue)
	{
		const auto currentTime = std::chrono::high_resolution_clock::now();
		const float deltaTime = std::chrono::duration<float>(currentTime - last_time).count();

		lag += deltaTime;
		timeManager.Update(deltaTime);



		bool inputState = input.ProcessInput();
		bool gameRunning = gameModeManager.IsGameRunning();

		if (!inputState || !gameRunning)
			doContinue = false;


;


		gameModeManager.Update(deltaTime);
		//while (lag >= fixed_time_step)
		//{
		//	//fixed_update(fixed_time_step);
		//	lag -= fixed_time_step;
		//}
		sceneManager.Update();


		eventDispatcher.ProcessEvents();  // Process events in the main loop



		renderer.Render();
		//sceneManager.FixedUpdate();
		const auto sleepTime = currentTime + std::chrono::milliseconds(msPerFrame) - std::chrono::high_resolution_clock::now();


		if (sleepTime.count() > 0)
		{
			std::this_thread::sleep_for(sleepTime);
		}

		last_time = currentTime;

		//sceneManager.FixedUpdate();



	}

	//eventManager.Shutdown();
	eventDispatcher.Shutdown();
}
