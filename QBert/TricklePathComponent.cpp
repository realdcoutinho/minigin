#include "TricklePathComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include <random>
#include <glm/vec2.hpp>
#include "TimeManager.h"
#include "Timer.h"
#include "GridNavigator.h"
#include "EnemyCharacterComponent.h"
#include "GridNode.h"

namespace dae
{
	TricklePathComponent::TricklePathComponent(GameObject& pOwner, TrickleType type)
		: BaseComponent(pOwner)
		, m_Type(type)
	{
	}

	TricklePathComponent::~TricklePathComponent()
	{

	}

	void TricklePathComponent::Update()
	{
		MovementUpdate();
	}

	void TricklePathComponent::MovementUpdate()
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
						/*GridNode* node = */TricklePath();
						//auto enemComp = GetOwner()->GetComponent<CharacterComponent>();
						//if (enemComp)
						//	enemComp->HandleInput(m_Direction);
						//auto navComp = GetOwner()->GetComponent<GridNavigator>();
						//if (navComp)
						//{
						//	navComp->MoveToIndex(node->GetNodeInfo().index);
						//}
				}
			}
		}
	}

	void TricklePathComponent::TricklePath()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1);
		int randomIndex = dis(gen);

		auto enemComp = GetOwner()->GetComponent<CharacterComponent>();
		auto navComp = GetOwner()->GetComponent<GridNavigator>();

		if (!navComp || ! enemComp)
			return;


		switch (m_Type)
		{
		case dae::TrickleType::Left:
		{
			LeftVectors vectors;
			if (randomIndex == 0)
			{
				m_Direction = vectors.LeftUp;
				navComp->MoveToDirection(m_Direction);
			}
			else
			{
				m_Direction = vectors.LeftDown;
				navComp->MoveToNextNode(false);
			}
			break;
		}
		case dae::TrickleType::Right:
		{
			RightVectors vectors;
			if (randomIndex == 0)
			{
				m_Direction = vectors.RightUp;
				navComp->MoveToDirection(m_Direction);
			}
			else
			{
				m_Direction = vectors.RightDown;
				navComp->MoveToNextNode(true);
			}
			break;
		}
		case dae::TrickleType::Down:
		{
			DownVectors vectors;
			if (randomIndex == 0)
			{
				m_Direction = vectors.DownLeft;
				navComp->MoveToDirection(m_Direction);
			}
			else
			{
				m_Direction = vectors.DownRight;
				navComp->MoveToDirection(m_Direction);
			}
			break;
		}
		}
		enemComp->HandleInput(m_Direction);
	}


	
}