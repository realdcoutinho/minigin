#include "PathFinderComponent.h"
#include "TriangularGrid.h"
#include "CharacterComponent.h"
#include <queue>
#include <unordered_map>
#include <limits>
#include "GridNavigator.h"

#include "TimeManager.h"
#include "Timer.h"
#include <iostream>
#include "GridNode.h"


namespace dae
{
	PathFinderComponent::PathFinderComponent(GameObject& pOwner, TriangularGrid& pGrid)
		: BaseComponent(pOwner)
		, m_Grid(pGrid)
	{
	}

	PathFinderComponent::~PathFinderComponent()
	{

	}

	void PathFinderComponent::Update()
	{
        if(!m_IsDead)
        {
            if (!m_CanMove)
            {
                auto& timer = TimeManager::GetInstance().GetTimer();

                m_MoveTimer += timer.GetElapsed();

                if (m_MoveTimer >= m_MoveTime)
                {
                    m_MoveTimer = 0.0f;
                    m_CanMove = false;
                    if (m_Path.size() > 0)
                    {
                        // Move to the next node in the path
                        //m_Path.erase(m_Path.begin());
                        GridNode* nextNode = m_Path[0];
                        m_Path.erase(m_Path.begin());


                        SendFacingStatesInput(*nextNode);
                        SendMovementInput(*nextNode);
                    }
                }
            }
        }
	}

	void PathFinderComponent::FindPath(GridNode& startNode, GridNode& targetNode)
	{
        m_CurrentNode = &startNode;
        m_TargetNode = &targetNode;
        m_Path.clear();

        std::unordered_map<GridNode*, float> distances;
        std::unordered_map<GridNode*, GridNode*> previous;
        std::priority_queue<std::pair<GridNode*, float>, std::vector<std::pair<GridNode*, float>>, NodeComparer> nodeQueue;

        for (auto node : m_Grid.GetNodes())
        {
            distances[node] = std::numeric_limits<float>::infinity();
            previous[node] = nullptr;
        }

        distances[m_CurrentNode] = 0.0f;
        nodeQueue.emplace(m_CurrentNode, 0.0f);

        while (!nodeQueue.empty())
        {
            GridNode* currentNode = nodeQueue.top().first;
            nodeQueue.pop();

            if (currentNode == m_TargetNode)
                break;

            if(currentNode->GetNodeInfo().type != TileType::Pit)
            {

                for (auto neighbor : m_Grid.GetConnectedNodes(currentNode->GetNodeInfo().index))
                {
                    float newDist = distances[currentNode] + glm::distance(currentNode->GetNodeInfo().centerPos, neighbor->GetNodeInfo().centerPos);
                    if (newDist < distances[neighbor])
                    {
                        distances[neighbor] = newDist;
                        previous[neighbor] = currentNode;
                        nodeQueue.emplace(neighbor, newDist);
                    }
                }
            }
        }

        // Reconstruct the path
        for (GridNode* at = m_TargetNode; at != nullptr; at = previous[at])
        {
            m_Path.push_back(at);
        }
        std::reverse(m_Path.begin(), m_Path.end());
        if(m_Path.size() < 1)
			throw std::runtime_error("Path not found");
        m_Path.erase(m_Path.begin()); //removes the first place, where he is at the momemnt, 
                                      //and makes the whole movement faster

	}

    glm::vec2 PathFinderComponent::FindDirectionToNextNode(GridNode& nextNode)
    {
        // Calculate direction vector
        
        glm::vec2 dir;

        auto currentPos = m_CurrentNode->GetNodeInfo().centerPos;
        auto nextPos = nextNode.GetNodeInfo().centerPos;

        if (nextPos.x > currentPos.x)
        {
            if (nextPos.y > currentPos.y)
            {
                dir.x = 1.0f;
                dir.y = 0.0f;
            }
            else if (nextPos.y < currentPos.y)
            {
                dir.x = 0.0f;
                dir.y = 1.0f;
            }
        }
        else if (nextPos.x < currentPos.x)
        {
            if (nextPos.y > currentPos.y)
            {
                dir.x = 0.0f;
                dir.y = -1.0f; //correto
            }
            else if (nextPos.y < currentPos.y)
            {
                dir.x = -1.0f;
                dir.y = 0.0f; //corrrto
            }
        }

        return dir;
    }

    void PathFinderComponent::SendFacingStatesInput(GridNode& nextNode)
    {
        glm::vec2 direction = FindDirectionToNextNode(nextNode);

        auto charComp = GetOwner()->GetComponent<CharacterComponent>();
        if (charComp)
            charComp->HandleInput(direction);
    }

    void PathFinderComponent::SendMovementInput(GridNode& nextNode)
    {
  //      glm::vec2 direction = FindDirectionToNextNode(nextNode);
		//auto enemp = GetOwner()->GetComponent<CharacterComponent>();
		//if (enemp)
		//	enemp->HandleInput(direction);
		//m_CanMove = true;


        auto gridNav = GetOwner()->GetComponent<GridNavigator>(); //WE ARE GONNA HAVE PROBLEMS WITH FACING DIRECTIONS
        if (gridNav)
            gridNav->MoveToNode(nextNode);
    }

}
