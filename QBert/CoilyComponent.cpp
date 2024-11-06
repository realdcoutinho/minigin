#include "CoilyComponent.h"
#include "GameObject.h"
#include "CharacterComponent.h"
#include "GridNavigator.h"
#include "TricklePathComponent.h"
#include "TriangularGrid.h"
#include "CoilyState.h"
#include "PathFinderComponent.h"
#include "LevelManager.h"
#include "GridNode.h"
#include <glm/vec2.hpp>

namespace dae
{
	CoilyComponent::CoilyComponent(GameObject& pOwner, TriangularGrid& grid, bool playableChar)
		: BaseComponent(pOwner)
		, m_IsPlayableChar(playableChar)
	{
		auto character = std::make_unique<CharacterComponent>(pOwner, CharacterType::Egg);
		m_Character = character.get();
		GetOwner()->AddComponent(std::move(character));
		m_Character->InitializeSprite(m_EggTextureFile, 1);
		m_Character->GetSprite()->SetScale({ 2.0f, 2.0f });



		auto node = grid.GetRandomTopStartNode();
		std::unique_ptr<GridNavigator> gridNavigator = std::make_unique<GridNavigator>(pOwner, grid, *node);
		m_Character->SetNavigator(gridNavigator.get());
		pOwner.AddComponent(std::move(gridNavigator));

		if(!m_IsPlayableChar)
		{
			std::unique_ptr<PathFinderComponent> pathFinder = std::make_unique<PathFinderComponent>(pOwner, grid);
			m_PathFinder = pathFinder.get();
			pOwner.AddComponent(std::move(pathFinder));
		}

		std::unique_ptr<TricklePathComponent> trickle = std::make_unique<TricklePathComponent>(pOwner, TrickleType::Down);
		m_TricklePath = trickle.get();
		pOwner.AddComponent(std::move(trickle));

		m_Character->GetSprite()->SetSegments(1);

		m_pCoilyState = std::make_unique<EggState>();
		m_pCoilyState->Enter();


		GetOwner()->SetLocalPosition(node->GetNodeInfo().centerPos);
	}

	CoilyComponent::~CoilyComponent()
	{

	}

	void CoilyComponent::Render()
	{

	}

	void CoilyComponent::Update()
	{
	}

	void CoilyComponent::HandleInput(GridNode& node)
	{
		std::unique_ptr newState = std::move(m_pCoilyState->HandleInput(this, node));
		if (newState)
		{
			m_pCoilyState->Exit();
			m_pCoilyState = std::move(newState);
			m_pCoilyState->Enter();
		}
	}

	void CoilyComponent::Evolve()
	{
		m_Character->InitializeSprite(m_CoilyTextureFile, 4);
		//if(!m_IsPlayableChar)
			GetOwner()->RemoveComponent(m_TricklePath);
	}

	void CoilyComponent::Hunt(GridNode& bertNode)
	{

		bertNode;
		//if(!m_IsPlayableChar)
		//{
		//	if (m_pCoilyState->GetState() == CoilyForm::Snake)
		//	{
		//		auto& node = m_Character->GetNavigator()->GetCurrentTile();

		//		bertNode.GetNodeInfo().index;
		//		m_PathFinder->FindPath(node, bertNode);
		//	}
		//}
	}

	void CoilyComponent::Hunt(std::vector<GameObject*> qberts)
	{
		if (!m_IsPlayableChar)
		{
			if (m_pCoilyState->GetState() == CoilyForm::Snake)
			{
				auto& node = m_Character->GetNavigator()->GetCurrentTile();
				auto& nodeInfo = node.GetNodeInfo();
				glm::vec2 CoilyPos = nodeInfo.centerPos;

				auto qbertOne = qberts[0];
				//cheack which distance is greater
				float distanceOne = 100000.0f;
				float distanceTwo = 100000.0f;

				if (!qberts[0]->IsActive())
				{
					//remove from vector
					qbertOne = qberts[1];
					qberts.erase(qberts.begin());
				}
				//if (!qberts[1])
				//{
				//	qberts.erase(qberts.begin() + 1);
				//}


				if (qbertOne)
				{
					auto qbertPos = qbertOne->GetComponent<CharacterComponent>()->GetNavigator()->GetCurrentTile().GetNodeInfo().centerPos;
					distanceOne = glm::distance(CoilyPos, qbertPos);
				}
				if (qberts.size()>1)
				{
					auto qBertTwo = qberts[1];
					auto qbertPos = qBertTwo->GetComponent<CharacterComponent>()->GetNavigator()->GetCurrentTile().GetNodeInfo().centerPos;
					distanceTwo = glm::distance(CoilyPos, qbertPos);
				}
				
				if (distanceOne < distanceTwo)
				{
					m_PathFinder->FindPath(node, qbertOne->GetComponent<CharacterComponent>()->GetNavigator()->GetCurrentTile());
					m_TargetQbert = qbertOne;
				}
				else
				{
					m_PathFinder->FindPath(node, qberts[1]->GetComponent<CharacterComponent>()->GetNavigator()->GetCurrentTile());
					m_TargetQbert = qberts[1];
				}
			}
		}
	}

}
