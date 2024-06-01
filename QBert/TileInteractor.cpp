#include "TileInteractor.h"
#include "QBertEvents.h"
#include "CharacterComponent.h"
#include "QBertCharacterComponent.h"
#include <iostream>
#include "ScoreComponent.h"
#include "TriangularGrid.h"
#include "EnemyCharacterComponent.h"
//
//dae::TileInteractor::TileInteractor(GameObject& pOwner, TriangularGrid& pGrid, unsigned int subID)
//	: BaseComponent(pOwner)
//	, IObserver(subID)
//	, m_CurrentTile(nullptr)
//	, m_TotalNumberTiles(36)
//	, m_CurrentSetTiles(0)
//	, m_pGrid(&pGrid)
//{
//
//}
//
//dae::TileInteractor::~TileInteractor()
//{
//}
//
//void dae::TileInteractor::Render()
//{
//}
//
//void dae::TileInteractor::Update()
//{
//}
//
//void dae::TileInteractor::OnNotify(BaseEvent* event)
//{
//	auto eve = dynamic_cast<DestroyCharacter*>(event);
//	if (eve != nullptr)
//	{
//		//eve->ExecuteEvent();
//	}
//
//
//	//auto eggEvolveEvent = dynamic_cast<EggEvolve*>(event);
//	//if (eggEvolveEvent != nullptr)
//	//{
//	//	auto gameObject = eggEvolveEvent->sender;
//	//	auto character = gameObject->GetComponent<EnemyCharacterComponent>();
//	//	if (character != nullptr)
//	//	{
//	//		eggEvolveEvent->ExecuteEvent();
//	//		return;
//	//	}
//	//}
//
//	//auto nodeEvent = dynamic_cast<TileChanger*>(event);
//	//if (nodeEvent != nullptr)
//	//{
//	//	auto gameObject = nodeEvent->sender;
//	//	auto character = gameObject->GetComponent<QBertCharacterComponent>();
//	//	if (character != nullptr)
//	//	{
//	//		if (nodeEvent->ExecuteEvent())
//	//		{
//	//			nodeEvent->IncrementScore();
//	//			m_CurrentSetTiles++;
//	//			if (m_CurrentSetTiles == m_TotalNumberTiles)
//	//			{
//	//				std::cout << "All tiles are set" << std::endl;
//	//				//m_pGrid->FlickerTextures(3000);
//	//				return;
//	//			}
//	//		}
//	//	}
//	//	auto enemy = gameObject->GetComponent<EnemyCharacterComponent>();
//	//	if (enemy != nullptr)
//	//	{
//	//		nodeEvent->ExecuteEventEnemy();
//	//	}
//	//}
//}
