#pragma once
#include "BaseComponent.h"
#include <vector>
#include <glm/vec2.hpp>


namespace dae
{


	class GridNode;
	class TriangularGrid;


	struct NodeComparer
	{
		bool operator()(std::pair<GridNode*, float> a, std::pair<GridNode*, float> b) const
		{
			return a.second > b.second; // For min-heap
		}
	};

	class PathFinderComponent final : public BaseComponent
	{
	public:
		PathFinderComponent(GameObject& pOwner, TriangularGrid& pGrid);
		~PathFinderComponent();
		PathFinderComponent(const PathFinderComponent&) = delete;
		PathFinderComponent(PathFinderComponent&&) = delete;
		PathFinderComponent& operator= (const PathFinderComponent&) = delete;
		PathFinderComponent& operator= (const PathFinderComponent&&) = delete;

		void Render() override {};
		void Update() override;

		void FindPath(GridNode& startNode, GridNode& targetNode);

		void Stop() { m_IsDead = true; }

	private:
		glm::vec2 FindDirectionToNextNode(GridNode& nextNode);
		void SendFacingStatesInput(GridNode& nextNode);
		void SendMovementInput(GridNode& nextNode);

		TriangularGrid& m_Grid;
		GridNode* m_CurrentNode;
		GridNode* m_TargetNode;
		std::vector<GridNode*> m_Path;

		bool m_IsDead = false;
		float m_MoveTimer = 0.0f;
		const float m_MoveTime = 0.9f;
		bool m_CanMove = false;
	};


}
