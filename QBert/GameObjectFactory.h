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
	class GameInfoLoader;
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
		GameObject& CreateHighScoreHUD(Scene& scene, int initialScore = 0);

		GameObject& CreatePlayerTitle(Scene& scene, int playerNumber = 1);

		GameObject& CreateStartMenu(Scene& scene);
		GameObject& CreateGameOver(Scene& scene, GameInfoLoader& gil, int playerOneScore, int playerTwoScore);
		GameObject& CreateVictoryScene(Scene& scene, GameInfoLoader& gil, int playerOneScore, int playerTwoScore);

		GameObject& CreateLevelOneTitle(Scene& scene);
		GameObject& CreateLevelTwoTitle(Scene& scene);
		GameObject& CreateLevelThreeTitle(Scene& scene);

		GameObject& CreateLevelSoloInstructions(Scene& scene);
		GameObject& CreateLevelCoopInstructions(Scene& scene);
		GameObject& CreateLevelVSInstructions(Scene& scene);

		GameObject& CreatePauseScreen(Scene& scene);

	private:
		friend class Singleton<GameObjectFactory>;
		~GameObjectFactory() = default;
	};
}


