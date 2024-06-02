#include "Listeners.h"
#include <iostream>
#include "QBertEvents.h"
#include "HUDComponent.h"
#include "TriangularGrid.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "QBertCharacterComponent.h"
#include "EnemyCharacterComponent.h"
#include "CoilyComponent.h"
#include "GridNode.h"
#include "EventDispatcher.h"
#include "GameModeManager.h"
#include "QBertGameMode.h"
#include "DeathComponent.h"
#include "HealthComponent.h"
#include <memory>
#include "HUDLivesComponent.h"
#include "EnemyManager.h"



namespace dae
{
    void ScoreListener::OnEvent(IEvent& event)
    {
        // We know that this listener is listening to PlayerScoredEvent
        auto& playerScoredEvent = dynamic_cast<ScoreEvent&>(event);
        // Check if the event is for this listener
        if (playerScoredEvent.getPlayerId() == listenerId)
        {
            if (m_Object.GetComponent<HUDComponent>())
            {
                m_Object.GetComponent<HUDComponent>()->SetValue(playerScoredEvent.getScore());
            }
            if (m_Object.GetComponent<ScoreComponent>())
            {
                m_Object.GetComponent<ScoreComponent>()->SetScore(playerScoredEvent.getScore());
            }
        }
    }

    std::vector<std::type_index> ScoreListener::GetSupportedEvents()
    {
        return { std::type_index(typeid(ScoreEvent)) };
    }

    void HealthListener::OnEvent(IEvent& event)
    {
        // We know that this listener is listening to PlayerHealthEvent
		auto& playerHealthEvent = dynamic_cast<PlayerHealthEvent&>(event);
		// Check if the event is for this listener
        if (playerHealthEvent.getPlayerId() == listenerId)
        {
            if (m_Object.GetComponent<HUDLivesComponent>())
            {
                m_Object.GetComponent<HUDLivesComponent>()->Hit();
			}
            if (m_Object.GetComponent<HealthComponent>())
            {
                int index = playerHealthEvent.getLastNodeIdx();
                auto healthComp = m_Object.GetComponent<HealthComponent>();
                healthComp->TakeHit();
                healthComp->Respawn(index);

			}
		}
    }

    std::vector<std::type_index> HealthListener::GetSupportedEvents()
    {
        return { std::type_index(typeid(PlayerHealthEvent)) };
    }

    void NodeListener::OnEvent(IEvent& event)
    {
        try
        {
            if (auto deathEvent = dynamic_cast<CharacterDeathEvent*>(&event))
            {
                if (deathEvent->GetId() == listenerId)
                {
                    GameObject& sender = deathEvent->GetSender();
                    auto charComp = sender.GetComponent<CharacterComponent>();
                    if (charComp)
                    {
                        auto charType = charComp->GetType();
                        switch (charType)
                        {
                        case CharacterType::QBert:
                            OnDeathEventQBert(*deathEvent);
                            break;
                        case CharacterType::Slick:
                        case CharacterType::Sam:
                            OnDeathEvent(*deathEvent);
                            break;
                        case CharacterType::Coily:
                            OnDeathEventCoily(*deathEvent);
                            break;
                        default:
                            // Handle unexpected character types if necessary
                            break;
                        }
                    }
                }
            }
            else if (auto nodeInteractorEvent = dynamic_cast<NodeInteractorEvent*>(&event))
            {
                if (nodeInteractorEvent->GetId() == listenerId)
                {
                    nodeInteractorEvent->GetNewNode().EnterNode(nodeInteractorEvent);

                    //auto& newNode = nodeInteractorEvent->GetNewNode();
                    //nodeInteractorEvent->GetOldNode().ExitNode(&nodeInteractorEvent->GetSender());
                    //newNode.EnterNode(&nodeInteractorEvent->GetSender(), &nodeInteractorEvent->GetOldNode());

                    //GameObject& sender = nodeInteractorEvent->GetSender();
                    //auto charComp = sender.GetComponent<CharacterComponent>();
                    //if (charComp)
                    //{
                    //    auto charType = charComp->GetType();
                    //    switch (charType)
                    //    {
                    //    case CharacterType::QBert:
                    //        //OnNodeEventPlayer(*nodeInteractorEvent);
                    //        auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
                    //        auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
                    //        if (qbertGameMode != nullptr)
                    //        {
                    //            //qbertGameMode->SetQBertNode(newNode);
                    //            qbertGameMode->QBertMovement();
                    //        }

                    //        break;
                    //    case CharacterType::Slick:
                    //    case CharacterType::Sam:
                    //        //OnNodeEventEnemy(*nodeInteractorEvent);
                    //        break;
                    //    case CharacterType::Coily:
                    //        //OnNodeEventCoily(*nodeInteractorEvent);
                    //        break;
                    //    default:
                    //        // Handle unexpected character types if necessary
                    //        break;
                    //    }
                    //}
                }
            }
            else if (auto upgradeNodeEvent = dynamic_cast<UpgradeNodeEvent*>(&event))
            {
                if (upgradeNodeEvent->GetId() == listenerId)
                {
                    OnNodeUpgradedEvent(*upgradeNodeEvent);
				}
			}
            else
            {
				// Handle unexpected events if necessary
			}

        }
        catch (const std::bad_cast& e)
        {
            // Handle or log the casting error
            std::cerr << "Casting error occurred: " << e.what() << '\n';
        }
    }

    std::vector<std::type_index> NodeListener::GetSupportedEvents()
    {
        return 
                {

                    std::type_index(typeid(CharacterDeathEvent)),
                    std::type_index(typeid(NodeInteractorEvent)),
                    std::type_index(typeid(UpgradeNodeEvent))

                };
    }


    ////NODE LISTENER
    //void NodeListener::OnNodeEventPlayer(NodeInteractorEvent& event)
    //{
    //    auto& newNode = event.GetNewNode();
    //    event.GetOldNode().ExitNode(&event.GetSender());
    //    newNode.EnterNode(&event.GetSender(), &event.GetOldNode());
    //    //if(newNode.GetNodeInfo().type != TileType::Pit)
    //    //{
    //    //    //auto scoreEvent = std::make_unique<ScoreEvent>(points, event.GetSender().GetID());
    //    //    //EventDispatcher::GetInstance().DispatchEvent(std::move(scoreEvent));

    //    //    points;
    //    //}


    //    //change this later to an event / listener system

    //}

    //void NodeListener::OnNodeEventEnemy(NodeInteractorEvent& event)
    //{
    //    event.GetOldNode().ExitNode(&event.GetSender());
    //    auto& newNode = event.GetNewNode();
    //    newNode.EnterNode(&event.GetSender());
    //}

    //void NodeListener::OnNodeEventCoily(NodeInteractorEvent& event)
    //{
    //    auto& newNode = event.GetNewNode();
    //    event.GetOldNode().ExitNode(&event.GetSender());
    //    newNode.EnterNode(&event.GetSender());
    //    //auto comp = event.GetSender().GetComponent<CoilyComponent>();
    //    //if (comp != nullptr)
    //    //{
    //    //    comp->HandleInput(event.GetNewNode());
    //    //}
    //}

    void NodeListener::OnDeathEventQBert(CharacterDeathEvent& event)
    {
        auto health = std::make_unique<PlayerHealthEvent>(event.GetSender().GetID(), event.GetLastNode().GetNodeInfo().index);
        EventDispatcher::GetInstance().DispatchEvent(std::move(health));
    }

    void NodeListener::OnDeathEventCoily(CharacterDeathEvent& event)
    {
        auto coily = event.GetSender().GetComponent<CoilyComponent>();
        auto qbertHunt = coily->GetTargetQbert();
        int points = coily->GetPoints();


        auto scoreEvent = std::make_unique<ScoreEvent>(points, qbertHunt->GetID());
        EventDispatcher::GetInstance().DispatchEvent(std::move(scoreEvent));

        auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(event.GetSender().GetID(), event.GetSender());
	    EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));

    }

    void NodeListener::OnDeathEvent(CharacterDeathEvent& event)
    {
        //go to enemy manager
        auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(event.GetSender().GetID(), event.GetSender());
        EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
    }

    void NodeListener::OnNodeUpgradedEvent(UpgradeNodeEvent& event)
    {
        bool isUpgraded = event.GetIsUpgrade();
        m_pGrid.NodeUpgraded(isUpgraded);
    }

    void EggListener::OnEvent(IEvent& event)
    {
        auto& eggEvent = dynamic_cast<EggEvolveEvent&>(event);
        if (eggEvent.GetId() != listenerId)
            return;

        GameObject& sender = eggEvent.GetSender();
        auto charComp = sender.GetComponent<EnemyCharacterComponent>();
        if (charComp == nullptr)
            return;

        auto type = charComp->GetType();
        if (type == CharacterType::Egg)
        {
            charComp->SetType(CharacterType::Coily);
            charComp->SetTextures();
        }
    }

    std::vector<std::type_index> EggListener::GetSupportedEvents()
    {
        return { std::type_index(typeid(EggEvolveEvent)) };
    }

    void EnemyListener::OnEvent(IEvent& event)
    {
        try
        {
            if (auto enemyDeath = dynamic_cast<EraseOneEnemyEvent*>(&event))
            {
                OnEnemyDeathEvent(*enemyDeath);
            }
            else if (auto AllEnemy = dynamic_cast<EraseAllEnemiesEvent*>(&event))
            {
                OnAllEnemiesDeathEvent(*AllEnemy);
            }

        }
        catch (const std::bad_cast& e)
        {
            // Handle or log the casting error
            std::cerr << "Casting error occurred: " << e.what() << '\n';
        }
    }

    std::vector<std::type_index> EnemyListener::GetSupportedEvents()
    {
        return
        {
            std::type_index(typeid(EraseOneEnemyEvent)),
            std::type_index(typeid(EraseAllEnemiesEvent))
        };
    }

    void EnemyListener::OnEnemyDeathEvent(EraseOneEnemyEvent& event)
    {
        auto& enemy = event.GetSender();
        m_EnemyManager->DestroyEnemy(&enemy);
    }

    void EnemyListener::OnAllEnemiesDeathEvent(EraseAllEnemiesEvent& event)
    {
        event;
        m_EnemyManager->DestroyAllEnemies();
    }

}
