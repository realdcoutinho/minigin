#pragma once
#include "BaseComponent.h"
#include <vector>
#include <memory>
#include <TextureComponent.h>
//include math library from sdl
#include <SDL.h>
//#include <SDL_image.h>
//#include <SDL_ttf.h>
//#include <SDL_mixer.h>
#include <glm/vec2.hpp>
#include <string>
#include "ResourceLibrary.h"
#include "ResourceManager.h"
#include "GameObject.h"



namespace dae 
{
	class GridNode;
	class Scene;
	struct GameInfo;
	class TriangularGrid final : public BaseComponent
	{
	public:
		TriangularGrid(GameObject& pOwner, Scene& scene, GameInfo& gi);
		~TriangularGrid() = default;
		TriangularGrid(const TriangularGrid& other) = delete;
		TriangularGrid(TriangularGrid&& other) noexcept = delete;
		TriangularGrid& operator=(const TriangularGrid& other) = delete;
		TriangularGrid& operator=(TriangularGrid&& other) noexcept = delete;

		void Render() override;
		void Update() override;
	
		GridNode& GetNode(int idx) 
		{ 
			return *m_GridNodes[idx]; 
		}
		GridNode* GetNextNode(int idx, glm::vec2 direction);
		GridNode* GetNextNode(GridNode* tile, glm::vec2 direction);
		glm::vec2& GetStartingPosition(glm::vec2 dir = glm::vec2(0, -1));
		GridNode& GetStartingNode(glm::vec2 dir = glm::vec2(0, -1));

		std::vector<GridNode*> GetNodes() { return m_GridNodes; }
		std::vector<GridNode*> GetConnectedNodes(int idx);
		GridNode* GetNodeAtPos(glm::vec2 pos);

		void UnregisterAllCharacters();
		void NodeUpgraded(bool isUpgarded);


		

	private:
		void CreateGridNodes(Scene& scene, GameInfo& gi);
		void GridCompleted();


		int m_Rows;
		int m_CurrentCompletedNodes{ 0 };
		int m_NrOfNodes{ 28 };
		std::vector<GridNode*> m_GridNodes;

		bool m_CanSwitch{ false };
		float m_SwitchTimer{ 0.0f };
	};


}
