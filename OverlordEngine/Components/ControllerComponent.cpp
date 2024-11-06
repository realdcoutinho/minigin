#include "stdafx.h"
#include "ControllerComponent.h"

ControllerComponent::ControllerComponent(const PxCapsuleControllerDesc& controllerDesc):
	m_ControllerDesc{ controllerDesc }
{
}

void ControllerComponent::Initialize(const SceneContext& /*sceneContext*/)
{
	if(!m_IsInitialized)
	{
		TODO_W7(L"Complete the ControllerComponent Intialization")

		//STEP1
		XMFLOAT3 position = GetGameObject()->GetTransform()->GetPosition();
		PxExtendedVec3 pos{ static_cast<PxReal>(position.x),  static_cast<PxReal>(position.y),  static_cast<PxReal>(position.z) };
		m_ControllerDesc.position = pos;

		//Step2
		m_ControllerDesc.userData = m_pController;

		//STEP3
		auto controllerManager = GetGameObject()->GetScene()->GetPhysxProxy()->GetControllerManager();
		m_pController = controllerManager->createController(m_ControllerDesc);

		//ASSERT_NULL(m_pController);
		if (m_pController == nullptr)
		{
			Logger::LogError(L"[ControllerComponent] Failed to create controller");
			return;
		}

		auto actor = m_pController->getActor();
		actor->userData = m_pController;
		
		SetCollisionGroup(static_cast<CollisionGroup>(m_CollisionGroups.word0));
		SetCollisionIgnoreGroup(static_cast<CollisionGroup>(m_CollisionGroups.word1));
	}
}

void ControllerComponent::OnSceneDetach(GameScene*)
{
	if (m_pController)
	{
		m_pController->getActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, true);
	}
}

void ControllerComponent::OnSceneAttach(GameScene*)
{
	if (m_pController)
	{
		m_pController->getActor()->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
	}
}

void ControllerComponent::OnOwnerAttach(GameObject* pOwner)
{
	pOwner->GetTransform()->SetControllerComponent(this);
}

void ControllerComponent::OnOwnerDetach(GameObject* pOwner)
{
	pOwner->GetTransform()->SetControllerComponent(nullptr);
}

void ControllerComponent::ApplyFilterData() const
{
	if (m_pController != nullptr)
	{
		const auto actor = m_pController->getActor();
		const auto numShapes = actor->getNbShapes();
		const auto shapes = new PxShape * [numShapes];

		const auto numPointers = actor->getShapes(shapes, numShapes);
		for (PxU32 i = 0; i < numPointers; i++)
		{
#pragma warning (push)
#pragma warning (disable: 6385)
			const auto shape = shapes[i];
#pragma warning (pop)
			shape->setSimulationFilterData(m_CollisionGroups);
			shape->setQueryFilterData(m_CollisionGroups);
		}
		delete[] shapes;
	}
}

void ControllerComponent::Translate(const XMFLOAT3& pos) const
{
	ASSERT_NULL_(m_pController);
	m_pController->setPosition(PhysxHelper::ToPxExtendedVec3(pos));
}

void ControllerComponent::Move(const XMFLOAT3& displacement, float minDistance)
{
	ASSERT_NULL_(m_pController);
	m_CollisionFlag = m_pController->move(PhysxHelper::ToPxVec3(displacement), minDistance, 0, nullptr, nullptr);
}

XMFLOAT3 ControllerComponent::GetPosition() const
{
	ASSERT_NULL_(m_pController);
	return PhysxHelper::ToXMFLOAT3(m_pController->getPosition());
}

XMFLOAT3 ControllerComponent::GetFootPosition() const
{
	ASSERT_NULL_(m_pController);
	return PhysxHelper::ToXMFLOAT3(m_pController->getFootPosition());
}

void ControllerComponent::SetCollisionGroup(CollisionGroup groups)
{
	m_CollisionGroups.word0 = PxU32(groups);
	ApplyFilterData();
}

void ControllerComponent::SetCollisionIgnoreGroup(CollisionGroup ignoreGroups)
{
	m_CollisionGroups.word1 = PxU32(ignoreGroups);
	ApplyFilterData();
}