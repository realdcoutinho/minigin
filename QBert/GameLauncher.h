#pragma once
#include <memory>


namespace dae
{
	class ResourceManager;
	class SceneManager;
	class ResourceLoader;
	class ServicesLoader;
	class GameInfoLoader;
	class QBertGameMode;
	class GameObjectFactory;
	class GameLauncher
	{
	public:
		GameLauncher();
		~GameLauncher();
		//void Initialize();
		//void Run();
		//void Cleanup();
	private:
		std::unique_ptr<ServicesLoader> m_ServicesLoader;
		std::unique_ptr<ResourceLoader> m_ResourceLoader;
		std::unique_ptr<GameInfoLoader> m_GameInfoLoader;
		QBertGameMode* m_GameMode;

		void LoadGameScenes();
		void LoadStartingScene(SceneManager& sm);
		void LoadInstructionsScene(SceneManager& sm);


		//void LoadGameSceneOne(SceneManager& sm);
		//void LoadMainMenu();
		//void LoadPauseMenu();
	};

}

