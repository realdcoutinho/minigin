#pragma once
#include "BaseComponent.h"
#include <memory>
#include <glm/vec2.hpp>
#include <vector>

namespace dae
{
	enum class TileType
	{
		TileOne,
		TileTwo,
		TileThree,
		Disc,
		Pit,
		Zero
	};

	class TextureComponent;
	struct NodeInfo
	{
		TileType type;
		glm::vec2 centerPos;
		TextureComponent* textureComp;
		int startColor;
		int leftDown;
		int rightDown;
		int leftUp;
		int rightUp;
		int index;
		bool hasEnemy{ false };
		bool hasCharacter{ false };
		bool hasSlickSam{ false };
		bool lastRow{ false };
	};

	class GridDisc final : public BaseComponent
	{
	public:
		GridDisc(GameObject& pOwner)
			: BaseComponent(pOwner) {};
		~GridDisc() = default;
		void Render() override {};
		void Update() override;
		TextureComponent* m_TextureComp;
	private:


	};


	class CharacterComponent;
	class NodeStates;
	struct GameInfo;
	class NodeInteractorEvent;
	class GridNode final : public BaseComponent
	{
	public:
		GridNode(GameObject& pOwner, NodeInfo info, GameInfo& gameInfo);

		~GridNode() = default;

		void Render() override {};
		void Update() override;

		NodeInfo& GetNodeInfo() { return m_NodeInfo; };

		int EnterNode(NodeInteractorEvent* nodeEvent);
		void ExitNode(GameObject* character);
		void UnResgister() { m_Characters.clear(); }
		void SetFlickeringState();
		void CheckOutCharacter(GameObject* character);

		int m_Level;
		int m_Points = 25;
		float m_CurrentTime = 0.0f;
		std::unique_ptr<NodeStates> m_NodeStates;
		GameObject* m_Disc;
	private:
		void CheckInCharacter(GameObject* character);
		
		int HandleInput(GameObject* character, GridNode* previousNode = nullptr);

		NodeInfo m_NodeInfo{};

		std::vector<GameObject*> m_Characters;
	};

}
