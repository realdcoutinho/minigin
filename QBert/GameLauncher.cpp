#include "GameLauncher.h"
#include "ServiceLocator.h"
#include "AudioSystem.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Scene.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "Command.h"
#include "InputManager.h"
#include "GameCommand.h"
#include "InputManager.h"
#include "Input.h"


#include "LevelManager.h"
#include "Listeners.h"
#include "HUDComponent.h"
#include "EventDispatcher.h"

#include "ResourceLoader.h"
#include "GameObjectFactory.h"
#include "ServicesLoader.h"
#include "GameInfoLoader.h"
#include "GameInfo.h"
#include "Levels.h"
#include "GameMode.h"
#include "QBertGameMode.h"
#include "GameModeManager.h"

#include <string>

namespace dae
{
	GameLauncher::GameLauncher()
	{
		m_GameInfoLoader = std::make_unique<GameInfoLoader>("../Data/");
		m_ServicesLoader = std::make_unique<ServicesLoader>();
		m_ResourceLoader = std::make_unique<ResourceLoader>();
		

		auto& gameMode = GameModeManager::GetInstance().CreateGameMode<QBertGameMode>("QBertGameMode");
		auto& qbertGameMode = dynamic_cast<QBertGameMode&>(gameMode);
		m_GameMode = &qbertGameMode;
		if (m_GameMode != nullptr)
		{
			m_GameMode->Initialize(m_GameInfoLoader.get());
			m_GameMode->LoadStartScene();
			//LoadGameScenes();
			//m_GameMode->StartScene("StartScene");
		}
	}

	GameLauncher::~GameLauncher()
	{

	}

	void GameLauncher::LoadGameScenes()
	{
		auto& sm = SceneManager::GetInstance();
		LoadStartingScene(sm);
		//LoadInstructionsScene(sm);
		//LoadGameSceneOne(sm);
	}

	void GameLauncher::LoadStartingScene(SceneManager& sm)
	{
		sm;
		auto& startScene = sm.CreateScene("StartScene");
		sm.SetActiveScene(startScene);

		////create big title
		//auto titleObject = std::make_unique<GameObject>();
		//titleObject.get()->InitializeTransformComponent();
		//titleObject.get()->SetLocalPosition(100, 100);

		//auto titleTexture = std::make_unique<TextureComponent>(*titleObject.get(), "Game Title.png", 1);
		//titleObject.get()->AddComponent(std::move(titleTexture));

		//startScene.Add(std::move(titleObject));

		////create options for the player
		//auto optionsObject = std::make_unique<GameObject>();
		//optionsObject.get()->InitializeTransformComponent();
		//optionsObject.get()->SetLocalPosition(100, 300);

		//auto soloObject = std::make_unique<GameObject>();
		//soloObject.get()->InitializeTransformComponent();
		//soloObject.get()->SetLocalPosition(0, 0);

		//auto font = ResourceManager::GetInstance().GetFont("Minecraft.ttf", 17);
		//auto soloText = std::make_unique<TextComponent>(*soloObject.get(), "SOLO PLAYING MODE", font);
		//soloObject.get()->AddComponent(std::move(soloText));

		//auto coopObject = std::make_unique<GameObject>();
		//coopObject.get()->InitializeTransformComponent();
		//coopObject.get()->SetLocalPosition(0, 50);
		//auto coopText = std::make_unique<TextComponent>(*coopObject.get(), "CO-OP PLAYING MODE", font);
		//coopObject.get()->AddComponent(std::move(coopText));

		//auto versusObject = std::make_unique<GameObject>();
		//versusObject.get()->InitializeTransformComponent();
		//versusObject.get()->SetLocalPosition(0, 100);
		//auto versusText = std::make_unique<TextComponent>(*versusObject.get(), "VERSUS PLAYING MODE", font);
		//versusObject.get()->AddComponent(std::move(versusText));

		//soloObject.get()->SetParent(optionsObject.get());
		//coopObject.get()->SetParent(optionsObject.get());
		//versusObject.get()->SetParent(optionsObject.get());

		//startScene.Add(std::move(optionsObject));
		//startScene.Add(std::move(soloObject));
		//startScene.Add(std::move(coopObject));
		//startScene.Add(std::move(versusObject));

		//auto selectObject = std::make_unique<GameObject>();
		//selectObject.get()->InitializeTransformComponent();
		//selectObject.get()->SetLocalPosition(100, 300);

		//auto selectTexture = std::make_unique<TextureComponent>(*selectObject.get(), "Egg.png", 1);
		//selectObject.get()->AddComponent(std::move(selectTexture));

		//auto selectMode = std::make_unique<SelectModeCommand>();


		//auto selectionCommand = std::make_unique<SelectionCommand>(*selectObject.get(), 300.f, 350.f, 400.f);
		//auto controllerIdx = dae::InputManager::GetInstance().GetControllerIdx();

		//startScene.Add(std::move(selectObject));

		//auto& input = startScene.GetSceneInput();
		//input.AddAxisCommand(controllerIdx, std::move(selectionCommand));
		//input.AddActionCommand(controllerIdx, dae::Controller::ControllerButton::A, std::move(selectMode));

		//sm.SetActiveScene(startScene);
	}

	void GameLauncher::LoadInstructionsScene(SceneManager& sm)
	{
		sm;
		/*auto& instructionsScene = sm.CreateScene("IntructionsScene");

		auto instructionsObject = std::make_unique<GameObject>();
		instructionsObject.get()->InitializeTransformComponent();
		instructionsObject.get()->SetLocalPosition(100, 100);

		auto instructionsTexture = std::make_unique<TextureComponent>(*instructionsObject.get(), "P1 Controls.png", 1);
		instructionsObject.get()->AddComponent(std::move(instructionsTexture));

		instructionsScene.Add(std::move(instructionsObject));*/
	}

	//void GameLauncher::LoadGameSceneOne(SceneManager& sm)
	//{
	//	////sm.CreateScene("StartScene");
	//	//sm.CreateScene("LevelOneSolo");
	//	//sm.CreateScene("LevelThreeCoop");

	//	sm;

	//	m_GameMode->LoadScene("LevelOneSolo");
	//	m_GameMode->LoadScene("LevelTwoSolo");
	//	m_GameMode->LoadScene("LevelThreeSolo");
	//	m_GameMode->LoadScene("LevelOneCoop");
	//	m_GameMode->LoadScene("LevelTwoCoop");
	//	m_GameMode->LoadScene("LevelThreeCoop");
	//	m_GameMode->LoadScene("LevelOneVS");
	//	m_GameMode->LoadScene("LevelTwoVS");
	//	m_GameMode->LoadScene("LevelThreeVS");

	//}


}

