#pragma once
#include "BaseComponent.h"
#include "TriangularGrid.h"

namespace dae
{
	class GridNode;
	struct NodeInfo;
	class GridNavigator : public BaseComponent
	{
	public:
		GridNavigator(GameObject& pOwner, TriangularGrid& pGrid, GridNode& startingNode);
		~GridNavigator();

		GridNavigator(const GridNavigator&) = delete;
		GridNavigator(GridNavigator&&) = delete;
		GridNavigator& operator= (const GridNavigator&) = delete;
		GridNavigator& operator= (const GridNavigator&&) = delete;

		void Render() override;
		void Update() override;

		void MoveToNode(GridNode& node);
		void MoveToDirection(const glm::vec2& direction, bool isDisc = false);
		void MoveToIndex(int idx);


		GridNode& GetCurrentTile() const { return *m_CurrentNode; }
		bool IsMoving() const { return m_IsMoving; }

		void SetNewPostion(int idx);
		void SetAlive() { m_IsAlive = true; }
		void SetDead() { m_IsAlive = false; }


	private:
		void Move(float delta);
		void CheckForPit(NodeInfo& nodeInfo);


		TriangularGrid* m_pGrid;
		GridNode* m_CurrentNode;
		GridNode* m_PreviousNode;
		GridNode* m_MovingToNode;

		float m_MoveTimer = 0.0f;
		const float m_MoveTime = 0.5f;
		bool m_CanMove = true;
		bool m_IsOnDisc = false;
		float m_MovementSpeed = 200.0f;

		glm::vec2 m_Pos{};
		glm::vec2 m_StartPos{};
		glm::vec2 m_TargetPos{};

		bool m_IsMoving = false;
		bool m_IsAlive = true;
	};

}

