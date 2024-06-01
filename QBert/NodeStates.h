#pragma once
#include "State.h"
#include <memory>
#include "CharacterComponent.h"

namespace dae
{
	enum class NodeType
	{
		One,
		Two,
		Three,
	};

	class GridNode;
	class NodeStates : public IState
	{
	public:
		NodeStates() = default;
		NodeStates(GridNode* node);
		//NodeStates(GridNode* node, bool enemyInteraction = false);
		NodeStates(GridNode* node, GameObject* character);
		virtual ~NodeStates() = default;

		//virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, bool enemyInteraction = false) = 0;
		virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, GameObject* character) = 0;
		virtual void Enter() override;
		virtual void Update() override = 0;
		virtual void Exit() override;
		bool GetChange() 
		{ 
			return positiveChange;
		}
	protected:
		GridNode* m_Node;
		GameObject* m_Character;
		bool m_IsEnemyInteraction{ false };
		bool positiveChange{ true };
	};

	class NodeStateOne final : public NodeStates
	{
	public:
		NodeStateOne() = default;
		//NodeStateOne(GridNode* node, bool enemyInteraction = false)
		//	: NodeStates(node, enemyInteraction) {}
		NodeStateOne(GridNode* node, GameObject* character)
			: NodeStates(node, character) {}

		//virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, bool enemyInteraction = false);
		virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, GameObject* character);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	class NodeStateTwo final : public NodeStates
	{
	public:

		NodeStateTwo() = default;
		//NodeStateTwo(GridNode* node, bool enemyInteraction = false)
		//	: NodeStates(node, enemyInteraction) {}
		NodeStateTwo(GridNode* node, GameObject* character)
			: NodeStates(node, character) {}

		//virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, bool enemyInteraction = false);
		virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, GameObject* character);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	class NodeStateThree final : public NodeStates
	{
	public:

		NodeStateThree() = default;
		//NodeStateThree(GridNode* node, bool enemyInteraction = false)
		//	: NodeStates(node, enemyInteraction) {}
		NodeStateThree(GridNode* node, GameObject* character)
			: NodeStates(node, character) {}

		//virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, bool enemyInteraction = false);
		virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, GameObject* character);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	};

	class NodeStateFlickering final : public NodeStates
	{
	public:

		NodeStateFlickering() = default;
		NodeStateFlickering(GridNode* node) 
			: NodeStates(node) {}

		//virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, bool enemyInteraction = false);
		virtual std::unique_ptr<NodeStates> HandleInput(GridNode* node, GameObject* character);
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;
	private:
		bool m_IsFlickering = false;
		int m_FlickerCount = 6;
		float m_CurrentTime = 0;
	};

}

