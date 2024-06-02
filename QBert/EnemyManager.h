#pragma once
#include <vector>

namespace dae
{
	struct GameInfo;
	class CoilyComponent;
	class Scene;
	class GridNode;
	class GameObject;
	class TriangularGrid;
	class EnemyManager
	{
	public:
		EnemyManager();
		~EnemyManager();

		void SetNewData(GameInfo& gameInfo);
		void SetCurrentScene(Scene* pScene) { m_pCurrentScene = pScene; }
		void SetTriangularGrid(TriangularGrid& pGrid) { m_pGrid = &pGrid; }

		void Update();
		void HuntQbert(std::vector<GameObject*> qberts);

		void DestroyCoily();
		void DestroyAllEnemies();
		void DestroyEnemy(GameObject* pEnemy);

		void Reset();

	private:

		void UpdateCoilySpawnTimers(float elapsedSec);
		void UpdateSlickSamSpawnTimers(float elapsedSec);
		void UpdateUggWrongwaySpawnTimers(float elapsedSec);

		void SpawnCoily();
		void SpawnSlickSam();
		void SpawnUggWrongway();

		bool m_VersusMode = false;

		bool m_SpawnCoily = false;
		bool m_SpawnSlickSam = false;
		bool m_SpawnUggWrongway = false;

		float m_SpawnTimerCoily = 0.f;
		float m_SpawnTimerSlickSam = 0.f;
		float m_SpawnTimerUggWrongway = 0.f;

		int m_MaxSlickSam = 2;
		int m_MaxUggWrongway = 2;

		int m_CurrentSlickSam = 0;
		int m_CurrentUggWrongway = 0;

		float m_CoilyInterval = 0.f;
		float m_SlickSamInterval = 0.f;
		float m_UggWrongwayInterval = 0.f;

		Scene* m_pCurrentScene;
		GameObject* m_pCoily;
		TriangularGrid* m_pGrid;

		std::vector<GameObject*> m_pEnemies;
	};
}



