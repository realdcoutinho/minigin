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
		}
	}

	GameLauncher::~GameLauncher()
	{

	}

	void GameLauncher::LoadStartingScene(SceneManager& sm)
	{
		sm;
		auto& startScene = sm.CreateScene("StartScene");
		sm.SetActiveScene(startScene);

	}
}

