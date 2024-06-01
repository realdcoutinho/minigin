#include "TricklePathComponent.h"
#include "BaseComponent.h"
#include "GameObject.h"
#include <random>
#include <glm/vec2.hpp>
#include "TimeManager.h"
#include "Timer.h"
#include "GridNavigator.h"
#include "EnemyCharacterComponent.h"

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
					glm::vec2 direction = TricklePath();
					auto enemComp = GetOwner()->GetComponent<CharacterComponent>();
					if (enemComp)
						enemComp->HandleInput(direction);
					auto navComp = GetOwner()->GetComponent<GridNavigator>();
					if (navComp)
					{
						navComp->MoveToDirection(direction);
					}
				}
			}
		}
	}

	glm::vec2 TricklePathComponent::TricklePath()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(0, 1);
		int randomIndex = dis(gen);

		switch (m_Type)
		{
			case dae::TrickleType::Left:
			{
				LeftVectors vectors;
				randomIndex == 0 ? vectors.LeftUp : vectors.LeftDown;
				break;
			}
			case dae::TrickleType::Right:
			{
				RightVectors vectors;
				return randomIndex == 0 ? vectors.RightUp : vectors.RightDown;
				break;
			}
			case dae::TrickleType::Down:
			{
				DownVectors vectors;
				return randomIndex == 0 ? vectors.DownLeft : vectors.DownRight;
				break;
			}
		}
		return glm::vec2();  // Return a default vector in case of an undefined type
	}
}