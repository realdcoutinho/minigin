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
#include "QBertEvents.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TransformComponent.h"
#include "TriangularGrid.h"
#include "Scene.h"

#include "ServiceLocator.h"
#include "AudioSystem.h"
#include "SoundLibrary.h"

namespace dae
{
    GridNode::GridNode(GameObject& pOwner, NodeInfo info, GameInfo& gameInfo, Scene* scene)
        : BaseComponent(pOwner),
        m_NodeInfo(info),
        m_Level(gameInfo.level)
    {
        m_NodeStates = std::make_unique<NodeStateOne>();

        if(m_NodeInfo.type == TileType::Pit)
			m_NodeStates = std::make_unique<NodeStatePit>();
        else if (m_NodeInfo.type == TileType::Disc)
        {
            int index = m_NodeInfo.index;
            std::vector<int> nums = { 2, 5, 9, 14, 20, 27, 35, 44 }; 



            auto discObj = std::make_unique<GameObject>();
            discObj->InitializeTransformComponent();
            if (std::find(nums.begin(), nums.end(), index) != nums.end()) 
            {
                discObj->SetLocalPosition(12.f, 15.0f);

            }
            else 
            {
                discObj->SetLocalPosition(9.f, 15.0f);
            }
            auto disc = std::make_unique<GridDisc>(*discObj);

            auto sprite = std::make_unique<TextureComponent>(*discObj, "Disk Spritesheet.png", 1);
            sprite.get()->SetTextureSegments({ 30.f, 1.f });
            sprite.get()->SetTexturePositionIndex({ 0.f, 0.f });
            sprite.get()->SetScale({ 2.0f, 2.0f });
            sprite.get()->nodesTest = true;
            disc->m_TextureComp = sprite.get();
            discObj->AddComponent(std::move(sprite));
            discObj->AddComponent(std::move(disc));

            m_Disc = discObj.get();
            discObj->SetParent(GetOwner());


            m_NodeStates = std::make_unique<NodeStateDisc>();

            scene->Add(std::move(discObj));
        }
        else if (m_NodeInfo.type == TileType::Zero)
            m_NodeStates = std::make_unique<NodeStateZero>();
	
      
        auto sprite = std::make_unique<TextureComponent>(pOwner);

		if (m_NodeInfo.type == TileType::TileOne)
        {
            sprite = std::make_unique<TextureComponent>(*GetOwner(), "Qbert Cubes.png", 2);
            sprite.get()->SetTextureSegments({ 6.f, 3.f });
            sprite.get()->SetTexturePositionIndex({ static_cast<float>(gameInfo.startColor), 0.f });
            sprite.get()->SetScale({ 2.0f, 2.0f });
            sprite.get()->nodesTest = true;
        }

        m_NodeInfo.textureComp = sprite.get();
        GetOwner()->AddComponent(std::move(sprite));
    }

    void GridNode::Update()
    {
        m_NodeStates->Update();
    }

    int GridNode::EnterNode(NodeInteractorEvent* nodeEvent)
    {
        nodeEvent->GetOldNode().ExitNode(&nodeEvent->GetSender());
        CheckInCharacter(&nodeEvent->GetSender());
        return HandleInput(&nodeEvent->GetSender(), &nodeEvent->GetOldNode());
    }

    void GridNode::ExitNode(GameObject* character)
    {
        CheckOutCharacter(character);
    }

    void GridNode::SetFlickeringState()
    {
        m_NodeStates = std::make_unique<NodeStateFlickering>(this);
    }



    void GridNode::CheckInCharacter(GameObject* character, bool neighbour)
    {
        auto charType = character->GetComponent<CharacterComponent>()->GetType();
        bool isPlayerDead = false;
        bool isSamDead = false;


        auto& soundSystem = dae::ServiceLocator::GetAudioService();
        bool isPit = false;
        if (m_NodeInfo.type == TileType::Pit)
            isPit = true;

        bool isDisc = false;
        if (m_NodeInfo.type == TileType::Disc)
            isDisc = true;

        bool isZero = false;
        if (m_NodeInfo.type == TileType::Zero)
            isZero = true;

        switch (charType)
        {
        case CharacterType::QBert:
            //search for coily in m_characters

            

            for (auto& chara : m_Characters)
            {
                if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Coily || chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Egg || chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Wrongway || chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Ugg)
                {
                    auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(chara->GetID(), *chara);
                    EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
                    isPlayerDead = true;
                    auto health = std::make_unique<PlayerHealthEvent>(character->GetID(), m_NodeInfo.index);
                    EventDispatcher::GetInstance().DispatchEvent(std::move(health));

                    m_Characters.erase(std::remove(m_Characters.begin(), m_Characters.end(), chara), m_Characters.end());

                    soundSystem->PlaySound(static_cast<unsigned short>(SoundID::QBertHit), 1);

                    break;
                }
                if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Sam || chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::Slick)
                {
                    auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(chara->GetID(), *chara);
                    EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
                    auto scoreEvent = std::make_unique<ScoreEvent>(300, character->GetID());
                    EventDispatcher::GetInstance().DispatchEvent(std::move(scoreEvent));
                    m_Characters.erase(std::remove(m_Characters.begin(), m_Characters.end(), chara), m_Characters.end());

                    soundSystem->PlaySound(static_cast<unsigned short>(SoundID::QBertJump), 1);
                    soundSystem->PlaySound(static_cast<unsigned short>(SoundID::SlickSamCaught), 1);

                    break;
                }
            }
            if (!isPlayerDead)
                m_Characters.push_back(character);

            if(isPit)
                soundSystem->PlaySound(static_cast<unsigned short>(SoundID::QBertFall), 1);
            if(isDisc)
                soundSystem->PlaySound(static_cast<unsigned short>(SoundID::DiskLift), 1);
            if (isZero)
            {
                soundSystem->StopSound(static_cast<unsigned short>(SoundID::DiskLift));
                soundSystem->PlaySound(static_cast<unsigned short>(SoundID::DiskLand), 1);
            }
            else
               soundSystem->PlaySound(static_cast<unsigned short>(SoundID::QBertJump), 1);

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
                    soundSystem->PlaySound(static_cast<unsigned short>(SoundID::SlickSamCaught), 1);


                    break;
                }
            }
            if (!isSamDead)
            {
                m_Characters.push_back(character);
                if (!isPit)
                    soundSystem->PlaySound(static_cast<unsigned short>(SoundID::OtherFoesJump), 1);
            }
            break;

        case CharacterType::Coily:
            for (auto& chara : m_Characters)
            {
                if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::QBert)
                {
                    auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(character->GetID(), *character);
                    EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
                    auto health = std::make_unique<PlayerHealthEvent>(chara->GetID(), m_NodeInfo.index);
                    EventDispatcher::GetInstance().DispatchEvent(std::move(health));
                    soundSystem->PlaySound(static_cast<unsigned short>(SoundID::QBertHit), 1);
                    break;
                }
            }
            m_Characters.push_back(character);
            //soundSystem->PlaySound(static_cast<unsigned short>(SoundID::CoilySnakeJump), 1);


            if (!isPit && !isDisc)
                soundSystem->PlaySound(static_cast<unsigned short>(SoundID::CoilySnakeJump), 1);
            if(isDisc)
                soundSystem->PlaySound(static_cast<unsigned short>(SoundID::CoilyFall), 1);

            break;
        case CharacterType::Egg:
            for (auto& chara : m_Characters)
            {
                if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::QBert)
                {
                    auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(character->GetID(), *character);
                    EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
                    auto health = std::make_unique<PlayerHealthEvent>(chara->GetID(), m_NodeInfo.index);
                    EventDispatcher::GetInstance().DispatchEvent(std::move(health));
                    soundSystem->PlaySound(static_cast<unsigned short>(SoundID::QBertHit), 1);

                    break;
                }
            }
            m_Characters.push_back(character);
            if (!isPit)
                soundSystem->PlaySound(static_cast<unsigned short>(SoundID::CoilyEggJump), 1);
            break;
        case CharacterType::Ugg:
            if (m_NodeInfo.type == TileType::Pit)
                return;
            if (neighbour)
            {
                for (auto& chara : m_Characters)
                {
                    if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::QBert)
                    {
                        auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(character->GetID(), *character);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
                        auto health = std::make_unique<PlayerHealthEvent>(chara->GetID(), m_NodeInfo.index);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(health));
                        soundSystem->PlaySound(static_cast<unsigned short>(SoundID::QBertHit), 1);
                        break;
                    }
                }
                m_Characters.push_back(character);
                soundSystem->PlaySound(static_cast<unsigned short>(SoundID::OtherFoesJump), 1);
            }
            else
            {
                auto grid = GetOwner()->GetParent()->GetComponent<TriangularGrid>();
                if (!grid)
                    return;
                int ldConnection = m_NodeInfo.leftDown;
                auto node = grid->GetNode(ldConnection);
                node->CheckInCharacter(character, true);
            }
            break;
        case CharacterType::Wrongway:
            if (m_NodeInfo.type == TileType::Pit)
                return;
            if(neighbour)
            {
                for (auto& chara : m_Characters)
                {
                    if (chara->GetComponent<CharacterComponent>()->GetType() == CharacterType::QBert)
                    {
                        auto enemyDeath = std::make_unique<EraseOneEnemyEvent>(character->GetID(), *character);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(enemyDeath));
                        auto health = std::make_unique<PlayerHealthEvent>(chara->GetID(), m_NodeInfo.index);
                        EventDispatcher::GetInstance().DispatchEvent(std::move(health));
                        soundSystem->PlaySound(static_cast<unsigned short>(SoundID::QBertHit), 1);

                        break;
                    }
                }
                m_Characters.push_back(character);
                soundSystem->PlaySound(static_cast<unsigned short>(SoundID::OtherFoesJump), 1);
            }
            else
            {
                auto grid = GetOwner()->GetParent()->GetComponent<TriangularGrid>();
                if (!grid)
                    return;
                int ldConnection = m_NodeInfo.rightDown;
                auto node = grid->GetNode(ldConnection);
                node->CheckInCharacter(character, true);
            }

        default:
            // Handle unexpected character types if necessary
            break;
        }
    }

    void GridNode::CheckOutCharacter(GameObject* character, bool neighbour)
    {
        if (character)
        {
            auto charType = character->GetComponent<CharacterComponent>()->GetType();

            switch (charType)
            {
            case CharacterType::Ugg:
                if (neighbour)
                {
                }
                else
                {
                    auto grid = GetOwner()->GetParent()->GetComponent<TriangularGrid>();
                    if (!grid)
                        return;
                    int ldConnection = m_NodeInfo.leftDown;
                    auto node = grid->GetNode(ldConnection);
                    if (!node)
                        return;
                    node->CheckOutCharacter(character, true);
                    return;
                }
            case CharacterType::Wrongway:
                if (neighbour)
                {
                }
                else
                {
                    auto grid = GetOwner()->GetParent()->GetComponent<TriangularGrid>();
                    if (!grid)
                        return;
                    int ldConnection = m_NodeInfo.rightDown;
                    auto node = grid->GetNode(ldConnection);
                    if (!node)
                        return;
                    node->CheckOutCharacter(character, true);
                    return;
                }
            }

            if (m_Characters.size() == 0)
                return;
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

    int GridNode::HandleInput(GameObject* character, GridNode* previousNode)
    {
        auto state = m_NodeStates->HandleInput(this, character, previousNode);
        if (state)
        {
            //if(m_NodeStates)
            //    m_NodeStates->Exit();
			//state->Exit();
			m_NodeStates = std::move(state);
			m_NodeStates->Enter();
   //         if (m_NodeStates->GetChange())
   //         {
			//	return m_Points;
			//}
   //         else
   //         {
			//	return -m_Points;
			//}
		}
        return 0;
    }

    void GridDisc::Update()
    {
    }
}
