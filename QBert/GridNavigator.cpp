#include "GridNavigator.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "TriangularGrid.h"
#include "CharacterComponent.h"
#include "QBertEvents.h"
#include "EventManager.h"
#include <memory>
#include "QBertCharacterComponent.h"
#include "TimeManager.h"
#include "Timer.h"
#include <iostream>
#include "EventDispatcher.h"
#include <cmath> // For std::sin
#include "GridNode.h"
#include "CoilyComponent.h"


namespace dae
{

	GridNavigator::GridNavigator(GameObject& pOwner, TriangularGrid& pGrid, GridNode& startingTile)
		: BaseComponent(pOwner)
		, m_pGrid(&pGrid)
		, m_CurrentNode(&startingTile)
		, m_CanMove(true)
		, m_MoveTimer(0.0f)
		, m_MoveTime(0.5f)
	{
		m_Pos = m_CurrentNode->GetNodeInfo().centerPos;
	}

	GridNavigator::~GridNavigator()
	{
	}

	void GridNavigator::Render()
	{
	}

	void GridNavigator::Update()
	{
		if (m_IsMoving)
		{
			//auto transform = GetOwner()->GetComponent<TransformComponent>();
			//if (!transform)
			//	return;

			auto& timer = TimeManager::GetInstance().GetTimer();
			float delta = timer.GetElapsed();

			Move(delta);

			GetOwner()->SetLocalPosition(m_Pos);
		}
	}

	void GridNavigator::MoveToNode(GridNode& node)
	{
		//if(!m_CanMove || !m_IsAlive)
		//	return;

		auto nodeInfo = node.GetNodeInfo();


		m_PreviousNode = m_CurrentNode;
		m_MovingToNode = &node;
		m_TargetPos = nodeInfo.centerPos;
		m_StartPos = m_Pos;
		m_IsMoving = true;
		m_CanMove = false;	
	}

	void GridNavigator::MoveToDirection(const glm::vec2& direction, bool isDisc)
	{
		if(!m_IsAlive)
		 return;

		m_IsOnDisc = isDisc;
		if (m_IsOnDisc)
			m_MovementSpeed /= 2;
		else
			m_MovementSpeed = 200.0f;


		auto nxNode = m_pGrid->GetNextNode(m_CurrentNode, direction);

		if (nxNode != nullptr)
		{
			MoveToNode(*nxNode);
		}
	}
	void GridNavigator::MoveToIndex(int idx)
	{
		auto node = m_pGrid->GetNode(idx);
		MoveToNode(*node);
	}

	void GridNavigator::MoveToNextNode(bool isPositive)
	{
		if(!m_IsAlive)
			return;
		auto nxNode = m_pGrid->GetNode(m_CurrentNode->GetNodeInfo().index + (isPositive ? 1 : -1));
		if (nxNode != nullptr)
		{
			MoveToNode(*nxNode);
		}
	}

	void GridNavigator::SetNewPostion(int idx)
	{
		if(!m_IsAlive)
			return;

		m_CurrentNode = m_pGrid->GetNode(idx);
		m_Pos = m_CurrentNode->GetNodeInfo().centerPos;
		m_TargetPos = m_Pos;
		m_StartPos = m_Pos;
		m_IsMoving = false;
		m_CanMove = true;
		m_IsAlive = true;

		auto transform = GetOwner()->GetComponent<TransformComponent>();
		if (!transform)
			return;	
		transform->SetPosition(m_Pos);



	}

	void GridNavigator::Move(float delta)
	{

		auto dir = m_TargetPos - m_Pos;
		float length = glm::length(dir);
		float moveDistance = m_MovementSpeed * delta;

		if (moveDistance > length)
		{
			m_Pos = m_TargetPos;
			m_IsMoving = false;

			//CheckForPit(m_CurrentNode->GetNodeInfo());
			
			m_CurrentNode = m_MovingToNode;
			auto nodeInteractor = std::make_unique<NodeInteractorEvent>(m_pGrid->GetOwnerID(), *GetOwner(), *m_PreviousNode, *m_CurrentNode);
			EventDispatcher::GetInstance().DispatchEvent(std::move(nodeInteractor));

	
		}
		else
		{
			dir = glm::normalize(dir);
			m_Pos += dir * moveDistance;
		}

				//m_MoveTimer += delta;
				//if (m_MoveTimer >= m_MoveTime)
				//{
				//	m_MoveTimer = m_MoveTime;
				//	m_IsMoving = false;
				//	m_CanMove = true;
				//}
				//float t = m_MoveTimer / m_MoveTime;
				//m_Pos = glm::mix(m_StartPos, m_TargetPos, t);
				//
				//
				//if (m_MoveTimer >= m_MoveTime)
				//{
				//	m_MoveTimer = 0.0f;
				//	m_Pos = m_TargetPos;
				//}
	}

	void GridNavigator::CheckForPit(NodeInfo& nodeInfo)
	{
		nodeInfo;
		//if (nodeInfo.type == TileType::Pit)
		//{
		//	//std::cout << "Char died to pit" << std::endl;
		//	m_IsAlive = false;
		//	auto death = std::make_unique<CharacterDeathEvent>(m_pGrid->GetOwnerID(), *m_PreviousNode, *GetOwner());
		//	EventDispatcher::GetInstance().DispatchEvent(std::move(death));
		//}
	}
}