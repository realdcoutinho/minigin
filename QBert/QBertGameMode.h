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
	class QBertGameMode final : public GameMode
	{	
		template <typename T, typename std::enable_if<std::is_base_of<GameMode, T>::value>::type*>
		friend GameMode& GameModeManager::CreateGameMode(const std::string& name);
	public:
		QBertGameMode(const std::string& name);
		virtual ~QBertGameMode() = default;

		void Initialize(GameInfoLoader* infoLoader) { m_pGameInfoLoader = infoLoader; };
		void Update(float elapsed) override;


		void StartScene(const std::string sceneName);
		void SetQBertNode(GridNode& node);


		void QBertMovement();
		void CanBertRender(bool render);

		TriangularGrid* GetGrid() const { return m_pGrid; };

	private:

		void LoadGrid();

		TriangularGrid* m_pGrid;


		GameObjectFactory* m_pGameObjectFactory;
		std::shared_ptr<EnemyManager> m_pEnemyManager;
		std::string m_CurrentSceneName;
		GameInfoLoader* m_pGameInfoLoader;
		GameInfo m_CurrentGameInfo;
		Scene* m_pCurrentScene;
		GridNode* m_pQBertNode;

		std::shared_ptr<EnemyListener> m_pEnemyListener;

		std::vector<GameObject*> m_pPlayers;


		int m_QBertLives;

	};


}
