#include "NodeStates.h"
#include "GameObject.h"
#include "TriangularGrid.h"
#include "GameObject.h"
#include "GridNode.h"
#include "CharacterComponent.h"
#include <iostream>
#include "DeathComponent.h"
#include "EventDispatcher.h"
#include "QBertEvents.h"
#include "RespawnComponent.h"
#include <memory>
#include "TimeManager.h"

namespace dae
{
    NodeStates::NodeStates(GridNode* node) 		: m_Node(node)
    {
    }

    //NodeStates::NodeStates(GridNode* tile, bool enemyInteraction)
    //    : m_Node(tile), m_IsEnemyInteraction(enemyInteraction)
    //{
    //}

    NodeStates::NodeStates(GridNode* node, GameObject* character)
        : m_Node(node), m_Character(character)
    {
    }


    void NodeStates::Enter()
    {
       

    }

    void NodeStates::Exit()
    {

    }


    //std::unique_ptr<NodeStates> NodeStateOne::HandleInput(GridNode* node, bool enemyInteraction)
    //{
    //    if (!enemyInteraction)
    //    {
    //        if (node->m_Level == 1)
    //        {

    //            return std::make_unique<NodeStateTwo>(node, enemyInteraction);
    //        }
    //        else if (node->m_Level == 2)
    //        {
    //            return std::make_unique<NodeStateTwo>(node, enemyInteraction);
    //        }
    //        else if (node->m_Level == 3)
    //        {
    //            return std::make_unique<NodeStateTwo>(node, enemyInteraction);
    //        }
    //    }
    //    // Blue state is the lowest state, cannot downgrade
    //    return nullptr;
    //}

    std::unique_ptr<NodeStates> NodeStateOne::HandleInput(GridNode* node, GameObject* character)
    {
        auto charType = character->GetComponent<CharacterComponent>()->GetType();
        if (charType == CharacterType::QBert)
        {
            if (node->m_Level == 1)
            {
                auto nodeUpgrade = std::make_unique<UpgradeNodeEvent>(node->GetOwner()->GetParent()->GetID(), true);
                EventDispatcher::GetInstance().DispatchEvent(std::move(nodeUpgrade));
                return std::make_unique<NodeStateTwo>(node, character);
            }
            else if (node->m_Level == 2)
            {
                return std::make_unique<NodeStateTwo>(node, character);
            }
            else if (node->m_Level == 3)
            {
                auto nodeUpgrade = std::make_unique<UpgradeNodeEvent>(node->GetOwner()->GetParent()->GetID(), true);
                EventDispatcher::GetInstance().DispatchEvent(std::move(nodeUpgrade));
                return std::make_unique<NodeStateTwo>(node, character);
            }
		}
        return std::make_unique<NodeStateOne>(node, character);

    }

    void NodeStateOne::Enter()
    {
        NodeStates::Enter();
        m_Node->GetNodeInfo().textureComp->SetTextureSegmentsY(static_cast<int>(NodeType::One));
    }

    void NodeStateOne::Update()
    {
        // Update logic for Blue state
    }

    void NodeStateOne::Exit()
    {
        NodeStates::Exit();
    }

    //std::unique_ptr<NodeStates> NodeStateTwo::HandleInput(GridNode* node, bool enemyInteraction)
    //{
    //    if (enemyInteraction)
    //    {
    //        // Downgrade logic: Orange to Blue
    //        return std::make_unique<NodeStateOne>(node, enemyInteraction);
    //    }
    //    else
    //    {
    //        if (node->m_Level == 2)
    //        {
    //            auto nodeUpgrade = std::make_unique<UpgradeNodeEvent>(node->GetOwner()->GetParent()->GetID(), true);
    //            EventDispatcher::GetInstance().DispatchEvent(std::move(nodeUpgrade));
    //            return std::make_unique<NodeStateThree>(node, enemyInteraction);
    //        }
    //        if (node->m_Level == 3)
    //        {
    //            return std::make_unique<NodeStateOne>(node, enemyInteraction);
    //        }
    //    }
    //    return nullptr;
    //}

    std::unique_ptr<NodeStates> NodeStateTwo::HandleInput(GridNode* node, GameObject* character)
    {
        auto charType = character->GetComponent<CharacterComponent>()->GetType();
        if (charType == CharacterType::QBert)
        {
            if (node->m_Level == 2)
            {
                auto nodeUpgrade = std::make_unique<UpgradeNodeEvent>(node->GetOwner()->GetParent()->GetID(), true);
                EventDispatcher::GetInstance().DispatchEvent(std::move(nodeUpgrade));
                return std::make_unique<NodeStateThree>(node, character);
            }
            if (node->m_Level == 3)
            {
                auto nodeUpgrade = std::make_unique<UpgradeNodeEvent>(node->GetOwner()->GetParent()->GetID(), false);
                EventDispatcher::GetInstance().DispatchEvent(std::move(nodeUpgrade));
                return std::make_unique<NodeStateOne>(node, character);
            }
        }
        if (charType == CharacterType::Slick || charType == CharacterType::Sam)
        {
            if (node->m_Level == 1 || node->m_Level == 3)
            {
                auto nodeUpgrade = std::make_unique<UpgradeNodeEvent>(node->GetOwner()->GetParent()->GetID(), false);
                EventDispatcher::GetInstance().DispatchEvent(std::move(nodeUpgrade));
            }
            return std::make_unique<NodeStateOne>(node, character);
		}
        
        return std::make_unique<NodeStateTwo>(node, character);
    }

    void NodeStateTwo::Enter()
    {
        NodeStates::Enter();
        int pos = static_cast<int>(NodeType::Two);
        m_Node->GetNodeInfo().textureComp->SetTextureSegmentsY(pos);
    }

    void NodeStateTwo::Update()
    {
        // Update logic for Orange state
    }

    void NodeStateTwo::Exit()
    {
        // Cleanup for Orange state
        NodeStates::Exit();

    }

    //std::unique_ptr<NodeStates> NodeStateThree::HandleInput(GridNode* node, bool enemyInteraction)
    //{

    //    if (enemyInteraction)
    //    {
    //        return std::make_unique<NodeStateTwo>(node, enemyInteraction);
    //    }
    //    // Yellow state is the highest state, cannot upgrade
    //    return nullptr;
    //}

    std::unique_ptr<NodeStates> NodeStateThree::HandleInput(GridNode* node, GameObject* character)
    {
        auto charType = character->GetComponent<CharacterComponent>()->GetType();
        if (charType == CharacterType::Slick || charType == CharacterType::Sam)
        {
            auto nodeUpgrade = std::make_unique<UpgradeNodeEvent>(node->GetOwner()->GetParent()->GetID(), false);
            EventDispatcher::GetInstance().DispatchEvent(std::move(nodeUpgrade));
            return std::make_unique<NodeStateTwo>(node, character);
        }
        return std::make_unique<NodeStateThree>(node, character);
    }

    void NodeStateThree::Enter()
    {
        NodeStates::Enter();
        m_Node->GetNodeInfo().textureComp->SetTextureSegmentsY(static_cast<int>(NodeType::Three));
        
    }

    void NodeStateThree::Update()
    {
        // Update logic for Yellow state
    }

    void NodeStateThree::Exit()
    {
        // Cleanup for Yellow state
        NodeStates::Exit();

    }


    //std::unique_ptr<NodeStates> NodeStateFlickering::HandleInput(GridNode* node, bool enemyInteraction)
    //{
    //    return std::unique_ptr<NodeStates>();
    //}
    std::unique_ptr<NodeStates> NodeStateFlickering::HandleInput(GridNode* node, GameObject* character)
    {
        node;
        character;
        return std::unique_ptr<NodeStates>();
    }

    void NodeStateFlickering::Enter()
    {
    }

    void NodeStateFlickering::Update()
    {

            if (m_FlickerCount >= 0)
            {
                m_CurrentTime += TimeManager::GetInstance().GetElapsed();
                if (m_CurrentTime > 0.0f)
                    m_Node->GetNodeInfo().textureComp->SetTexturePositionIndex({ m_Node->GetNodeInfo().startColor, 1.f });
                if (m_CurrentTime > 0.1f)
                    m_Node->GetNodeInfo().textureComp->SetTexturePositionIndex({ m_Node->GetNodeInfo().startColor, 2.f });
                if (m_CurrentTime > 0.2f)
                    m_Node->GetNodeInfo().textureComp->SetTexturePositionIndex({ m_Node->GetNodeInfo().startColor, 0.f });
                if (m_CurrentTime > 0.3f)
                {
                    m_CurrentTime = 0.0f;
                    m_FlickerCount--;
                }
                if (m_FlickerCount == 0)
                {
                    m_Node->GetNodeInfo().textureComp->SetTexturePositionIndex({ m_Node->GetNodeInfo().startColor,  m_Node->m_Level });
                    if (m_Node->m_Level == 3)
                        m_Node->GetNodeInfo().textureComp->SetTexturePositionIndex({ m_Node->GetNodeInfo().startColor,  m_Node->m_Level - 2 });
                }
            }
    }
    void NodeStateFlickering::Exit()
    {
    }
}
