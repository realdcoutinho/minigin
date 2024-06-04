#ifndef QBERT_EVENTS_H
#define QBERT_EVENTS_H

#include "BaseEvent.h"
#include "TriangularGrid.h"
#include "GameObject.h"
#include "ScoreComponent.h"
#include "CharacterComponent.h"
#include "EnemyCharacterComponent.h"
#include "QBertCharacterComponent.h"
#include <thread>
#include <chrono>
#include <future>
#include <iostream>
#include "TriangularGrid.h"

namespace dae
{

	class GameObject;

	enum class EventType : unsigned int
	{
		Empty,
		HealthChange,
		ScoreChange,
		PlayerDeath,
		SoundPlay,
		TileChange,
		LevelComplete,
		EggEvolve,
		EnemyDeath,
	};

	class ScoreEvent final : public IEvent
	{


	public:
		ScoreEvent(int s, int id) : IEvent(), score(s), playerId(id)
		{
		}
		// Method to get the score
		int getScore() const {
			return score;
		}

		// Method to get the player ID
		int getPlayerId() const {
			return playerId;
		}
	private:
		int score;
		int playerId;
	};

	class ScoreEventHUD final : public IEvent
	{


	public:
		ScoreEventHUD(int s, int id) : IEvent(), score(s), playerId(id)
		{
		}
		// Method to get the score
		int getScore() const {
			return score;
		}

		// Method to get the player ID
		int getPlayerId() const {
			return playerId;
		}
	private:
		int score;
		int playerId;
	};

	class PlayerHealthEvent final : public IEvent
	{
	public:
		PlayerHealthEvent(int id, int idx) : IEvent(), playerId(id), lastNodeIdx(idx)
		{
		}

		// Method to get the player ID
		int getPlayerId() const {
			return playerId;
		}

		// Method to get the last node index
		int getLastNodeIdx() const {
			return lastNodeIdx;
		}

	private:
		int playerId;
		int lastNodeIdx;
	};

	class HealthChangeEventHUD final : public IEvent
	{
	public:
		HealthChangeEventHUD(int id, int value) : IEvent(), playerId(id), value(value)
		{
		}

		// Method to get the player ID
		int getPlayerId() const {
			return playerId;
		}

		// Method to get the last node index
		int getValue() const {
			return value;
		}

	private:
		int playerId;
		int value;
	};

	class CharacterDeathEvent : public IEvent
	{
	public:
		CharacterDeathEvent(int id, GridNode& lastNode, GameObject& sender) : IEvent(), m_Id(id), m_LastNode(lastNode), m_Sender(sender) {}
		~CharacterDeathEvent() {}
		GameObject& GetSender() { return m_Sender; }
		int GetId() { return m_Id; }
		GridNode& GetLastNode() { return m_LastNode; }

	private:
		GameObject& m_Sender;
		GridNode& m_LastNode;
		int m_Id;
	};


	class NodeInteractorEvent : public IEvent
	{
	public:
		NodeInteractorEvent(int id, GameObject& sender, GridNode& nodeOld, GridNode& nodeNew) : IEvent(), m_Sender(sender), m_NodeOld(nodeOld), m_NodeNew(nodeNew), m_Id(id) {}
		~NodeInteractorEvent() {}

		GridNode& GetOldNode() { return m_NodeOld; }
		GridNode& GetNewNode() { return m_NodeNew; }
		GameObject& GetSender() { return m_Sender; }
		int GetId() { return m_Id; }

	private:
		GridNode& m_NodeOld;
		GridNode& m_NodeNew;
		GameObject& m_Sender;
		int m_Id;
	};


	class UnresgisterNodes : public IEvent
	{
		public:
		UnresgisterNodes(int id, GameObject& sender) : IEvent(), m_Id(id), m_Sender(sender) {}
		~UnresgisterNodes() {}
		GameObject& GetSender() { return m_Sender; }
		int GetId() { return m_Id; }

		private:
			GameObject& m_Sender;
			int m_Id;
	};

	class UpgradeNodeEvent final : public IEvent
	{
	public:
		UpgradeNodeEvent(int id, bool isUpgrade) : IEvent(), m_Id(id), m_IsUpgrade(isUpgrade) {}
		~UpgradeNodeEvent() {}
		int GetId() { return m_Id; }
		bool GetIsUpgrade() { return m_IsUpgrade; }

	private:
		int m_Id;
		bool m_IsUpgrade;
	};



	class EraseOneEnemyEvent : public IEvent
	{
		public:
		EraseOneEnemyEvent(int id, GameObject& sender) : IEvent(), m_Id(id), m_Sender(sender) {}
		~EraseOneEnemyEvent() {}
		GameObject& GetSender() { return m_Sender; }
		int GetId() { return m_Id; }

		private:
			GameObject& m_Sender;
			int m_Id;
	};

	class EraseAllEnemiesEvent : public IEvent
	{
		public:
		EraseAllEnemiesEvent(int id) : IEvent(), m_Id(id) {}
		~EraseAllEnemiesEvent() {}
		int GetId() { return m_Id; }

		private:
			int m_Id;

	};

	class EggEvolveEvent : public IEvent
	{
		public:
		EggEvolveEvent(int id, GameObject& sender) : IEvent(),  m_Id(id), m_Sender(sender) {}
		~EggEvolveEvent() {}

		GameObject& GetSender() { return m_Sender; }
		int GetId() { return m_Id; }

	private:
		GameObject& m_Sender;
		int m_Id;
	};



}
#endif QBERT_EVENTS_H
