#pragma once
#include <memory>
#include "Singleton.h"
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	class TriangularGrid;
	struct GameInfo;
	class Scene;
	class GridNode;
	class GameObjectFactory final : public Singleton<GameObjectFactory>
	{
		public:
		GameObjectFactory() = default;

		GameObject& InitializePlayerOne(Scene& scene, TriangularGrid& pGrid, GameInfo& gi);
		GameObject& InitializePlayerTwo(Scene& scene, TriangularGrid& pGrid, GameInfo& gi);

		GameObject& CreateCoily(Scene& scene, TriangularGrid& pGrid, bool isPlayable = false);
		GameObject& CreateQbert(Scene& scene, TriangularGrid& pGrid, int startingNode, int player);
		GameObject& CreateSlickSam(Scene& scene, TriangularGrid& pGrid);
		GameObject& CreateUggWrongway(Scene& scene, TriangularGrid& pGrid);

		GameObject& CreateGrid(Scene& scene,GameInfo& gi);
		GameObject& CreateTargetColorNode(Scene& scene, GameInfo& gi);

		GameObject& CreateHUDScore(Scene& scene, glm::vec2& pos, int initialScore = 0);
		GameObject& CreateHUDLives(Scene& scene, glm::vec2& pos, int initialLives = 3);
		GameObject& CreateHUDLevel(Scene& scene, int initialLevel = 1);
		GameObject& CreateHUDFPS(Scene& scene);

		GameObject& CreateStartMenu(Scene& scene);
		GameObject& CreateGameOver(Scene& scene, int playerOneScore, int playerTwoScore);

		GameObject& CreateLevelOneTitle(Scene& scene);
		GameObject& CreateLevelTwoTitle(Scene& scene);
		GameObject& CreateLevelThreeTitle(Scene& scene);

		//GameObject& CreateGridNode(Scene& scene, GameInfo& gi, glm::vec2& pos, int col, int row, int rows, int width, int height, int index);
	private:
		friend class Singleton<GameObjectFactory>;
		~GameObjectFactory() = default;
	};
}


