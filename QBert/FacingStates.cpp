#include "FacingStates.h"
#include <iostream>
#include "GameObject.h"
#include "CharacterComponent.h"
#include "GridNavigator.h"
#include "TextComponent.h"
#include "GameObject.h"

#include <map>
#include <functional>



namespace dae
{
	FacingStates::FacingStates(GameObject* character, const glm::vec2& input)
		:m_Character{ character }
		, m_Input{ input }
	{
	}


	std::unique_ptr<FacingStates> FacingStates::HandleInput(GameObject* character, const glm::vec2& input)
	{
		if (input.x == 0 && input.y == 1)
		{
			return std::make_unique<RightUp>(character, input);
		}
		if (input.x == -1 && input.y == 0)
		{
			return std::make_unique<LeftUp>(character, input);
		}
		if (input.x == 1 && input.y == 0)
		{
			return std::make_unique<RightDown>(character, input);
		}
		if (input.x == 0 && input.y == -1)
		{
			return std::make_unique<LeftDown>(character, input);
		}
		return nullptr;
	}

	void FacingStates::Enter()
	{
		//auto move = m_Character->GetComponent<GridNavigator>();
		//move->MoveToDirection(m_Input);
	}

	std::unique_ptr<FacingStates> RightUp::HandleInput(GameObject* character, const glm::vec2& input)
	{
		return FacingStates::HandleInput(character, input);
	}

	void RightUp::Enter()
	{
		FacingStates::Enter();
		auto text = m_Character->GetComponent<TextureComponent>();
		text->SetSegments(static_cast<int>(FacingDirection::RightUp));
	}

	void RightUp::Update()
	{
	}

	void RightUp::Exit()
	{
	}


	std::unique_ptr<FacingStates> RightDown::HandleInput(GameObject* character, const glm::vec2& input)
	{
		return FacingStates::HandleInput(character, input);
	}

	void RightDown::Enter()
	{
		FacingStates::Enter();
		auto text = m_Character->GetComponent<TextureComponent>();
		text->SetSegments(static_cast<int>(FacingDirection::RightDown));
	}

	void RightDown::Update()
	{
	}

	void RightDown::Exit()
	{
	}

	std::unique_ptr<FacingStates> LeftUp::HandleInput(GameObject* character, const glm::vec2& input)
	{
		return FacingStates::HandleInput(character, input);
	}

	void LeftUp::Enter()
	{
		FacingStates::Enter();
		auto text = m_Character->GetComponent<TextureComponent>();
		text->SetSegments(static_cast<int>(FacingDirection::LeftUp));
	}

	void LeftUp::Update()
	{
	}

	void LeftUp::Exit()
	{
	}

	std::unique_ptr<FacingStates> LeftDown::HandleInput(GameObject* character, const glm::vec2& input)
	{
		return FacingStates::HandleInput(character, input);
	}

	void LeftDown::Enter()
	{
		FacingStates::Enter();
		auto text = m_Character->GetComponent<TextureComponent>();
		text->SetSegments(static_cast<int>(FacingDirection::LeftDown));
	}

	void LeftDown::Update()
	{
	}

	void LeftDown::Exit()
	{
	}

};