#pragma once
#include <memory>


namespace dae
{
	class SceneManager;
	class ResourceLoader;
	class ServicesLoader;
	class GameInfoLoader;
	class QBertGameMode;
	class GameLauncher
	{
	public:
		GameLauncher();
		~GameLauncher();

	private:
		std::unique_ptr<ServicesLoader> m_ServicesLoader;
		std::unique_ptr<ResourceLoader> m_ResourceLoader;
		std::unique_ptr<GameInfoLoader> m_GameInfoLoader;
		QBertGameMode* m_GameMode;


		void LoadStartingScene(SceneManager& sm);
	};

}

