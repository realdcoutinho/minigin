#include "SelectModeComponent.h"
#include "TextureComponent.h"
#include "GameObject.h"
#include <memory>
#include <glm/glm.hpp>
#include "SelectModeStates.h"

namespace dae
{
	SelectModeComponent::SelectModeComponent(GameObject& pOwner)
		:BaseComponent(pOwner)
	{
		auto arrow = std::make_unique<TextureComponent>(pOwner, "Selection Arrow.png");
		m_pArrow = arrow.get();
		arrow->SetScale({5.0f, 5.0f});
		pOwner.AddComponent(std::move(arrow));

		m_pState = std::make_unique<SoloMode>(&pOwner);
	}

	SelectModeComponent::~SelectModeComponent()
	{
		// Cleanup if necessary
	}

	void SelectModeComponent::Render()
	{
	}

	void SelectModeComponent::Update()
	{
	}

	void SelectModeComponent::HandleInput(glm::vec2 direction)
	{
		auto newState = std::move(m_pState->HandleInput(GetOwner(), direction));
		if (newState)
		{
			m_pState = std::move(newState);  // m_pGameStates must be declared as std::unique_ptr<GameStates>
			m_pState->Enter();
		}
	}
	void SelectModeComponent::SelectMode()
	{
		m_pState->SelectGameMode();
	}
}

