#include "GridNode.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "NodeStates.h"
#include "GameInfo.h"
#include "CharacterComponent.h"
#include "QBertEvents.h"
#include <iostream>
#include "DeathComponent.h"
#include "EventDispatcher.h"
#include "QBertEvents.h"
#include "RespawnComponent.h"
#include "TricklePathComponent.h"
#include "PathFinderComponent.h"
#include "TimeManager.h"



namespace dae
{
    GridNode::GridNode(GameObject& pOwner, NodeInfo info, GameInfo& gameInfo)
        : BaseComponent(pOwner),
        m_NodeInfo(info),
        m_Level(gameInfo.level)
    {
        m_NodeStates = std::make_unique<NodeStateOne>();
        auto sprite = std::make_unique<TextureComponent>(pOwner);

        if (m_NodeInfo.type == TileType::Pit)
        {
            sprite = std::make_unique<TextureComponent>(*GetOwner(), "Inactive.png", 1);
		}
        else if (m_NodeInfo.type == TileType::Disc)
        {
			//sprite = std::make_unique<TextureComponent>(*GetOwner(), "Disc.png", 1);
		}
		else
            sprite = std::make_unique<TextureComponent>(*GetOwner(), "Qbert Cubes.png", 2);

       
        sprite.get()->SetTextureSegments({6.f, 3.f});
        sprite.get()->SetTexturePositionIndex({ static_cast<float>(gameInfo.startColor), 0.f});
        sprite.get()->SetScale({ 2.0f, 2.0f });
        sprite.get()->nodesTest = true;
        m_NodeInfo.textureComp = sprite.get();
        GetOwner()->AddComponent(std::move(sprite));
    }

    void GridNode::Update()
    {
        m_NodeStates->Update();
    }

    int GridNode::EnterNode(GameObject* character)
    {
        if(m_NodeInfo.type == TileType::Pit)
            return 0;

        CheckInCharacter(character);
        return HandleInput(character);
    }

    void GridNode::ExitNode(GameObject* character)
    {
        CheckOutCharacter(character);
    }

    void GridNode::SetFlickeringState()
    {
        m_NodeStates = std::make_unique<NodeStateFlickering>(this);
    }



    void GridNode::CheckInCharacter(GameObject* character)
    {
        if (m_Characters.size() == 0)
        {
            m_Characters.push_back(character);
            return;
        }
        else
        {
            auto charType = character->GetComponent<CharacterComponent>()->GetType();
            bool isPlayerDead = false;
            bool isSamDead = false;

            switch (charType)
            {
            case CharacterType::QBert:
                //search for coily in m_characters
                for (auto& chara : m_Characters)
                {
                    if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Coily || chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Wrongway)
                    {
                        auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(chara->GetID(), *chara);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
                        isPlayerDead = true;
                        auto health = std::make_unique<PlayerHealthEvent>(character->GetID(), m_NodeInfo.index);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(health));

                        m_Characters.erase(std::remove(m_Characters.begin(), m_Characters.end(), chara), m_Characters.end());
                        break;
                    }
                    if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Sam || chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Slick)
                    {
                        auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(chara->GetID(), *chara);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
                        auto scoreEvent = std::make_unique<ScoreEvent>(300, character->GetID());
                        EventDispatcher::GetInstance().DispatchEvent(std::move(scoreEvent));
                        m_Characters.erase(std::remove(m_Characters.begin(), m_Characters.end(), chara), m_Characters.end());
                        break;
                    }
                }
                if (!isPlayerDead)
                    m_Characters.push_back(character);
                break;

            case CharacterType::Slick:
            case CharacterType::Sam:
                for (auto& chara : m_Characters)
                {
                    if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::QBert)
                    {
                        auto scoreEvent = std::make_unique<ScoreEvent>(300, chara->GetID());
                        EventDispatcher::GetInstance().DispatchEvent(std::move(scoreEvent));
                        isSamDead = true;

                        auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(character->GetID(), *character);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));


                        break;
                    }
                }
                if (!isSamDead)
                {
                    m_Characters.push_back(character);
                }
                break;

            case CharacterType::Coily:
            case CharacterType::Egg:
            case CharacterType::Ugg:
            case CharacterType::Wrongway:
                for (auto& chara : m_Characters)
                {
                    if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::QBert)
                    {
                        auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(character->GetID(), *character);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
                        auto health = std::make_unique<PlayerHealthEvent>(chara->GetID(), m_NodeInfo.index);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(health));
                        break;
                    }
                }
                m_Characters.push_back(character);
                break;

            default:
                // Handle unexpected character types if necessary
                break;
            }
        }







        //auto info = m_NodeInfo;

        //auto charType = character->GetComponent<CharacterComponent>()->GetType();
        //switch (charType)
        //{
        //case CharacterType::QBert:
        //    if (m_NodeInfo.hasEnemy)
        //    {
        //        m_NodeInfo.hasCharacter = false;
        //        //std::cout << "Qbert dies1" << std::endl;
        //       // std::cout << "Qbert for playe1r" << std::endl;
        //        auto health = std::make_unique<PlayerHealthEvent>(character->GetID(), 40);
        //        EventDispatcher::GetInstance().DispatchEvent(std::move(health));
        //        break;
        //    }
        //    else if (m_NodeInfo.hasSlickSam)
        //    {
        //        //sam deis
        //        //points for player
        //        //std::cout << "Sam dies1" << std::endl;
        //       // std::cout << "Points for playe1r" << std::endl;
        //        m_NodeInfo.hasCharacter = true;
        //        auto scoreEvent = std::make_unique<ScoreEvent>(300, character->GetID());
        //        EventDispatcher::GetInstance().DispatchEvent(std::move(scoreEvent));
        //        break;
        //    }
        //    m_NodeInfo.hasCharacter = true;
        //    //std::cout << "Qbert enters:" << info.index << std::endl;
        //    break;
        //case CharacterType::Slick:
        //case CharacterType::Sam:
        //    if (m_NodeInfo.hasCharacter)
        //    {
        //        //samslick dies
        //        //points for player
        //        //std::cout << "Sam dies2" << std::endl;

        //        m_NodeInfo.hasSlickSam = false;

        //        character->GetComponent<DeathComponent>()->OnDeath();
        //        //auto scoreEvent = std::make_unique<ScoreEvent>(300, m_Character->GetID());
        //        //EventDispatcher::GetInstance().DispatchEvent(std::move(scoreEvent));

        //        break;
        //    }
        //    m_NodeInfo.hasSlickSam = true;
        //    break;
        //case CharacterType::Coily:
        //case CharacterType::Egg:
        //case CharacterType::Ugg:
        //case CharacterType::Wrongway:
        //    if (m_NodeInfo.hasCharacter)
        //    {
        //        //qbert dies
        //        m_NodeInfo.hasCharacter = false;
        //        m_NodeInfo.hasEnemy = false;
        //        //std::cout << "Qbert dies2" << std::endl;
        //        break;
        //    }
        //    m_NodeInfo.hasEnemy = true;
        //    break;
        //default:
        //    // Handle unexpected character types if necessary
        //    break;
        //}

    }

    void GridNode::CheckOutCharacter(GameObject* character)
    {
        if (character)
        {
            //search character in m_character and remove if exists
            for (auto it = m_Characters.begin(); it != m_Characters.end(); ++it)
            {
                if ((*it) == character)
                {
					m_Characters.erase(it);
					break;
				}
			}
        }
    }

    int GridNode::HandleInput(GameObject* character)
    {
        auto state = m_NodeStates->HandleInput(this, character);
        if (state)
        {
			//state->Exit();
			m_NodeStates = std::move(state);
			m_NodeStates->Enter();
            if (m_NodeStates->GetChange())
            {
				return m_Points;
			}
            else
            {
				return -m_Points;
			}
		}
        return 0;
    }
}

//
//int GridNode::HandleInput(bool enemyInteraction)
//{
//    auto state = m_NodeStates->HandleInput(this, enemyInteraction);
//    if (state)
//    {
//        state->Exit();
//        m_NodeStates = std::move(state);
//        m_NodeStates->Enter();
//        if (m_NodeStates->GetChange())
//        {
//            return m_Points;
//        }
//        else
//        {
//            return -m_Points;
//        }
//    }
//    return 0;
//}