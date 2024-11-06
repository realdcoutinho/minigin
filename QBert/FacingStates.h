#pragma once
#include "State.h"
#include <glm/glm.hpp>
#include <memory>





namespace dae
{
	enum class FacingDirection
	{
		RightUp,//
		LeftUp,
		RightDown,
		LeftDown//
	};

	class GameObject;
	class RightUp;
	class LeftUp;
	class RightDown;
	class LeftDown;
	class FacingStates : public IState
	{
	public:
		FacingStates() = default;
		FacingStates(GameObject* character, const glm::vec2& input);
		virtual ~FacingStates() = default;
		virtual std::unique_ptr<FacingStates> HandleInput(GameObject* character, const glm::vec2& input);
		virtual void Enter() override;
		virtual void Update() override = 0;
		virtual void Exit() override = 0;

	protected:
		GameObject* m_Character;
		glm::vec2 m_Input;
	};

	class RightUp final : public FacingStates
	{
	public:
		RightUp() = default;
		RightUp(GameObject* character, const glm::vec2& input)
			: FacingStates(character, input)
		{
		}
		virtual ~RightUp() = default;
		virtual std::unique_ptr<FacingStates> HandleInput(GameObject* character, const glm::vec2& input) override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	
	class RightDown final : public FacingStates
	{
		public:
		RightDown() = default;
			RightDown(GameObject* character, const glm::vec2& input)
				: FacingStates(character, input)
			{
		}
		virtual ~RightDown() = default;
		virtual std::unique_ptr<FacingStates> HandleInput(GameObject* character, const glm::vec2& input) override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};


	class LeftUp final : public FacingStates
	{
	public:
		LeftUp() = default;
		LeftUp(GameObject* character, const glm::vec2& input)
			: FacingStates(character, input)
		{
		}
		virtual ~LeftUp() = default;
		virtual std::unique_ptr<FacingStates> HandleInput(GameObject* character, const glm::vec2& input) override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	class LeftDown final : public FacingStates
	{
	public:
		LeftDown() = default;
		LeftDown(GameObject* character, const glm::vec2& input)
			: FacingStates(character, input)
		{
		}
		virtual ~LeftDown() = default;
		virtual std::unique_ptr<FacingStates> HandleInput(GameObject* character, const glm::vec2& input) override;
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

}
