#pragma once
#include "GameMode.h"
#include "GameModeManager.h"
#include "GameObjectFactory.h"
#include <memory>
#include "GameInfo.h"


namespace dae
{
	class GameObjectFactory;
	class GameInfoLoader;
	struct GameInfo;
	class Scene;
	class EnemyManager;
	class GridNode;
	class TriangularGrid;
	class EnemyListener;
	class LevelState;
	class QBertGameMode final : public GameMode
	{	
		template <typename T, typename std::enable_if<std::is_base_of<GameMode, T>::value>::type*>
		friend GameMode& GameModeManager::CreateGameMode(const std::string& name);
	public:
		QBertGameMode(const std::string& name);
		virtual ~QBertGameMode() = default;

		void Initialize(GameInfoLoader* infoLoader) { m_pGameInfoLoader = infoLoader; };
		void Update(float elapsed) override;

		void LoadStartScene();
		void Restart();

		void StartScene(const std::string sceneName);
		void LoadScene(const std::string sceneName);
		void GameOver();
		
		void LoadNextScene();


		void QBertMovement();
		void CanBertRender(bool render);

		TriangularGrid* GetGrid() const { return m_pGrid; };

		void ResetEnemyManager();

		int GetPlayerOneLives() const { return m_PlayerOneLives; };
		int GetPlayerOneScore() const { return m_PlayerOneScore; };
		int GetPlayerTwoLives() const { return m_PlayerTwoLives; };
		int GetPlayerTwoScore() const { return m_PlayerTwoScore; };

		void SetPlayerLives(int lives, int player);
		void SetPlayerScore(int score, int player);

		void SetLevelState(std::string& startScene);
		void SetTitleScene(const std::string& startScene);

	private:

		void CreatePlayers(Scene& scene);

		void CreateTitleScenes();


		TriangularGrid* m_pGrid;


		GameObjectFactory* m_pGameObjectFactory;
		std::shared_ptr<EnemyManager> m_pEnemyManager;
		std::string m_CurrentSceneName;
		GameInfoLoader* m_pGameInfoLoader;
		GameInfo m_CurrentGameInfo;
		Scene* m_pCurrentScene;
		GridNode* m_pQBertNode;

		std::shared_ptr<EnemyListener> m_pEnemyListener;
		std::shared_ptr<LevelState> m_pLevelState;

		std::vector<GameObject*> m_pPlayers;


		int m_PlayerOneLives{ 3 };
		int m_PlayerOneScore{ 0 };
		int m_PlayerTwoLives{ 3 };
		int m_PlayerTwoScore{ 0 };


	};


}
