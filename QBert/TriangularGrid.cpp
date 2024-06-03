#include "TriangularGrid.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include "SceneManager.h"
#include "Scene.h"
#include <algorithm>
#include <iostream>
#include "CharacterComponent.h"
#include "NodeStates.h"
#include "GridNode.h"
#include "GameObjectFactory.h"
#include "GameInfo.h"
#include "GameModeManager.h"
#include "QBertGameMode.h"
#include "TimeManager.h"


namespace dae
{
    


    TriangularGrid::TriangularGrid(GameObject& pOwner, Scene& scene, GameInfo& gi)
        : BaseComponent(pOwner),
        m_Rows(10)
    {
       CreateGridNodes(scene, gi);
       CreateTopStartNodes(scene, gi);
       CreateLeftStartNodes(scene, gi);
       CreateRightStartNodes(scene, gi);
    }

    void TriangularGrid::CreateGridNodes(Scene& scene, GameInfo& gi)
    {
        int gridNodeSize = 64;
        int windowWidth = 640;
        int yOffset = 20;
        int index = 0;

        glm::vec2 pos{ windowWidth / 2.f - gridNodeSize / 2.f, yOffset };
        yOffset = 20;

        for (int row = 0; row < (m_Rows); ++row)
        {
            pos.x = windowWidth / 2.f - (row + 1) * gridNodeSize/2;
            for (int col = 0; col <= row; ++col)
            {
                std::unique_ptr<dae::GameObject> curTile = std::make_unique<dae::GameObject>();
                curTile->InitializeTransformComponent();
                curTile->SetLocalPosition(pos.x, pos.y);

                pos.x += gridNodeSize;

                NodeInfo nodeInfo;
                nodeInfo.leftDown = (row == (m_Rows)-1) ? -1 : index + row + 1;
                nodeInfo.leftUp = (col == 0) ? -1 : index - (row + 1);
                nodeInfo.rightDown = (row == (m_Rows)-1) ? -1 : nodeInfo.leftDown + 1;
                nodeInfo.rightUp = (col == row) ? -1 : index - row;
                nodeInfo.centerPos = { pos.x - gridNodeSize / 2.f - 20.0f, pos.y - gridNodeSize / 2.f + 20.0f };
                nodeInfo.index = index;
                nodeInfo.startColor = gi.startColor;

                // Determine the type based on the node's position in the grid
                if (row < 2 || col == 0 || col == row || row > 8)
                {
                    nodeInfo.type = TileType::Pit;
                    //nodeInfo.index = -1; // Optionally reset the index for perimeter nodes
                }
                else
                {
                    nodeInfo.type = TileType::TileOne;
                }

                if (row == 8)
                {
                    nodeInfo.lastRow = true;
                }

                if (index == 15)
                {
                    nodeInfo.leftDown = 0;
                    nodeInfo.leftUp = 0;
                    nodeInfo.rightDown = 0;
                    nodeInfo.rightUp = 0;
                    nodeInfo.type = TileType::Disc;
                }
                if (index == 0)
                {
                    nodeInfo.type = TileType::Zero;
                    nodeInfo.leftDown = 4;
                    nodeInfo.leftUp = 4;
                    nodeInfo.rightDown = 4;
                    nodeInfo.rightUp = 4;
                }

                std::unique_ptr<GridNode> node = std::make_unique<GridNode>(*curTile.get(), nodeInfo, gi);
                m_GridNodes.push_back(node.get());
                curTile->AddComponent(std::move(node));
                curTile->SetParent(GetOwner());
                scene.Add(std::move(curTile));

                ++index;
            }
            pos.y += gridNodeSize - yOffset;
        }
    }

    void TriangularGrid::CreateTopStartNodes(Scene& scene, GameInfo& gi)
    {
        glm::vec2 pos1 = m_GridNodes[7]->GetNodeInfo().centerPos;
        glm::vec2 pos2 = m_GridNodes[4]->GetNodeInfo().centerPos;
        glm::vec2 pos3 = m_GridNodes[8]->GetNodeInfo().centerPos;

        pos1.y -= 250.0f;
        pos2.y -= 200.0f;
        pos3.y -= 250.0f;

        std::unique_ptr<dae::GameObject> startNode1 = std::make_unique<dae::GameObject>();
        startNode1->InitializeTransformComponent();
        startNode1->SetLocalPosition(pos1.x, pos1.y);

        NodeInfo nodeInfo;
        nodeInfo.leftDown =7;
        nodeInfo.leftUp = 7;
        nodeInfo.rightDown = 7;
        nodeInfo.rightUp =7;
        nodeInfo.centerPos = pos1;
        nodeInfo.index = 55;
        nodeInfo.type = TileType::Zero;

        std::unique_ptr<GridNode> node1 = std::make_unique<GridNode>(*startNode1.get(), nodeInfo, gi);
        m_GridNodes.push_back(node1.get());
        m_TopStartNodes.push_back(node1.get());
        startNode1->AddComponent(std::move(node1));
        startNode1->SetParent(GetOwner());
        scene.Add(std::move(startNode1));

        std::unique_ptr<dae::GameObject> startNode2 = std::make_unique<dae::GameObject>();
        startNode2->InitializeTransformComponent();
        startNode2->SetLocalPosition(pos2.x, pos2.y);

        NodeInfo nodeInfo2;
        nodeInfo2.centerPos = pos2;
        nodeInfo2.index = 56;
        nodeInfo2.leftDown = 4;
        nodeInfo2.leftUp = 4;
        nodeInfo2.rightDown = 4;
        nodeInfo2.rightUp = 4;
        nodeInfo2.type = TileType::Zero;

        std::unique_ptr<GridNode> node2 = std::make_unique<GridNode>(*startNode2.get(), nodeInfo2, gi);
        m_GridNodes.push_back(node2.get());
        m_TopStartNodes.push_back(node2.get());
        startNode2->AddComponent(std::move(node2));
        startNode2->SetParent(GetOwner());
        scene.Add(std::move(startNode2));

        std::unique_ptr<dae::GameObject> startNode3 = std::make_unique<dae::GameObject>();
        startNode3->InitializeTransformComponent();
        startNode3->SetLocalPosition(pos3.x, pos3.y);

        NodeInfo nodeInfo3;
        nodeInfo3.centerPos = pos3;
        nodeInfo3.index = 57;
        nodeInfo3.leftDown = 8;
        nodeInfo3.leftUp = 8;
        nodeInfo3.rightDown = 8;
        nodeInfo3.rightUp = 8;
        nodeInfo3.type = TileType::Zero;

        std::unique_ptr<GridNode> node3 = std::make_unique<GridNode>(*startNode3.get(), nodeInfo3, gi);
        m_GridNodes.push_back(node3.get());
        m_TopStartNodes.push_back(node3.get());
        startNode3->AddComponent(std::move(node3));
        startNode3->SetParent(GetOwner());
        scene.Add(std::move(startNode3));
    }

    void TriangularGrid::CreateLeftStartNodes(Scene& scene, GameInfo& gi)
    {
        glm::vec2 pos1 = m_GridNodes[36]->GetNodeInfo().centerPos;
        pos1.x -= 75.0f;

        std::unique_ptr<dae::GameObject> startNode1 = std::make_unique<dae::GameObject>();
        startNode1->InitializeTransformComponent();
        startNode1->SetLocalPosition(pos1.x, pos1.y);

        NodeInfo nodeInfo;
        nodeInfo.leftDown = 37;
        nodeInfo.leftUp = 37;
        nodeInfo.rightDown = 37;
        nodeInfo.rightUp = 37;
        nodeInfo.centerPos = pos1;
        nodeInfo.index = 58;
        nodeInfo.type = TileType::Zero;

        std::unique_ptr<GridNode> node1 = std::make_unique<GridNode>(*startNode1.get(), nodeInfo, gi);
        m_GridNodes.push_back(node1.get());
        m_LeftStartNode = node1.get();
        startNode1->AddComponent(std::move(node1));
        startNode1->SetParent(GetOwner());
        scene.Add(std::move(startNode1));       
            
    }

    void TriangularGrid::CreateRightStartNodes(Scene& scene, GameInfo& gi)
    {
        glm::vec2 pos1 = m_GridNodes[44]->GetNodeInfo().centerPos;
        pos1.x += 75.0f;

        std::unique_ptr<dae::GameObject> startNode1 = std::make_unique<dae::GameObject>();
        startNode1->InitializeTransformComponent();
        startNode1->SetLocalPosition(pos1.x, pos1.y);

        NodeInfo nodeInfo;
        nodeInfo.leftDown = 43;
        nodeInfo.leftUp = 43;
        nodeInfo.rightDown = 43;
        nodeInfo.rightUp = 43;
        nodeInfo.centerPos = pos1;

        nodeInfo.index = 59;
        nodeInfo.type = TileType::Zero;

        std::unique_ptr<GridNode> node1 = std::make_unique<GridNode>(*startNode1.get(), nodeInfo, gi);
        m_GridNodes.push_back(node1.get());
        m_RightStartNode = node1.get();
        startNode1->AddComponent(std::move(node1));
        startNode1->SetParent(GetOwner());
        scene.Add(std::move(startNode1));
    }

    void TriangularGrid::Render()
    {

    }

    void TriangularGrid::Update()
    {
        if (m_CanSwitch)
        {
            m_SwitchTimer += TimeManager::GetInstance().GetElapsed();
            if (m_SwitchTimer > 4.0f)
            {
                auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
                auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
                if (qbertGameMode != nullptr)
                {
                    qbertGameMode->LoadNextScene();
                    m_CanSwitch = false;
                }
			}
        }
    }

    void TriangularGrid::NodeUpgraded(bool isUpgarded)
    {
        if (isUpgarded)
            m_CurrentCompletedNodes++;
        else
            m_CurrentCompletedNodes--;

        if (m_CurrentCompletedNodes == m_NrOfNodes)
            GridCompleted();

        std::cout << "Current completed nodes: " << m_CurrentCompletedNodes << std::endl;
    }

    GridNode* TriangularGrid::GetRandomTopStartNode()
    {   
        int random = rand() % m_TopStartNodes.size();
		return m_TopStartNodes[random];
    }

    GridNode* TriangularGrid::GetLeftStartNode()
    {
        return m_LeftStartNode;
    }

    GridNode* TriangularGrid::GetRightStartNode()
    {
        return m_RightStartNode;
    }

    void TriangularGrid::GridCompleted()
    {
        std::cout << "Grid completed" << std::endl;
        for (auto node : m_GridNodes)
        {
			//node->SetNodeState(NodeState::Completed);
            node->SetFlickeringState();
		}
		m_CanSwitch = true;
    }





    GridNode* dae::TriangularGrid::GetNextNode(int idx, glm::vec2 direction)
    {
        // TODO: insert return statement here
        auto node = m_GridNodes[idx];
        auto info = node->GetNodeInfo();
        if (direction.x == 0 && direction.y > 0)
        {
            if (info.rightUp != -1)
                return m_GridNodes[info.rightUp];
        }
        else if (direction.x < 0 && direction.y == 0)
        {
            if (info.leftUp != -1)
                return m_GridNodes[info.leftUp];
        }
        else if (direction.x > 0 && direction.y == 0)
        {
            if (info.rightDown != -1)
                return m_GridNodes[info.rightDown];
        }
        else if (direction.x == 0 && direction.y < 0)
        {
            if (info.leftDown != -1)
                return m_GridNodes[info.leftDown];
        }
        return nullptr;
    }

    GridNode* TriangularGrid::GetNextNode(GridNode* node, glm::vec2 direction)
    {
        auto& info = node->GetNodeInfo();
        int idx = info.index;
        return GetNextNode(idx, direction);
    }

    GridNode& TriangularGrid::GetStartingNode(glm::vec2 dir)
    {
        size_t startingPos{0};
        if (dir.y == -1 && dir.x == 0)
        {
            startingPos = 4; // starting positin for those starting at the top
        }
        if (dir.y == 0 && dir.x == 1)
        {
            startingPos = 46; // starting positon for those starting on the right
        }
        if (dir.y == 0 && dir.x == -1)
        {
            startingPos = 53; // starting positin for those starting at the left
        }
        return *m_GridNodes[startingPos];
    }

    std::vector<GridNode*> TriangularGrid::GetConnectedNodes(int idx)
    {
        m_GridNodes[idx]->GetNodeInfo();
        std::vector<GridNode*> connectedNodes;
        auto& info = m_GridNodes[idx]->GetNodeInfo();
        if (info.leftDown != -1)
        {
			connectedNodes.push_back(m_GridNodes[info.leftDown]);
		}
        if (info.leftUp != -1)
        {
            connectedNodes.push_back(m_GridNodes[info.leftUp]);
        }
        if (info.rightDown != -1)
        {
			connectedNodes.push_back(m_GridNodes[info.rightDown]);
		}
        if (info.rightUp != -1)
        {
			connectedNodes.push_back(m_GridNodes[info.rightUp]);
		}
		return connectedNodes;
    }

    GridNode* TriangularGrid::GetNodeAtPos(glm::vec2 pos)
    {
        for (auto& node : m_GridNodes)
        {
            if (node->GetNodeInfo().centerPos == pos)
            {
				return node;
			}
		}
        return nullptr;
    }

    void TriangularGrid::UnregisterAllCharacters()
    {
        for (auto& node : m_GridNodes)
        {
            node->UnResgister();
		}
    }



    glm::vec2& TriangularGrid::GetStartingPosition(glm::vec2 dir)
    {
        size_t startingPos{ 0 };
        if (dir.y == -1 && dir.x == 0)
        {
            startingPos = 4; // starting positin for those starting at the top
        }
        if (dir.y == 0 && dir.x == 1)
        {
            startingPos = 46; // starting positon for those starting on the right
        }
        if (dir.y == 0 && dir.x == -1)
        {
            startingPos = 53; // starting positin for those starting at the left
        }
        return m_GridNodes[startingPos]->GetNodeInfo().centerPos;
    }


}










