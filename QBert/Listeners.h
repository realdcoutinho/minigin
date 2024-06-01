#pragma once
#include "IEventListener.h"



namespace dae
{
    //class PlayerScoredEvent;
    class GameObject;
    class ScoreListener final : public IEventListener
    {
    public:
        ScoreListener() = default;
        ScoreListener(GameObject& gameObj, int id) : m_Object(gameObj), listenerId(id) {}

        void OnEvent(IEvent& event) override;

        std::vector<std::type_index> GetSupportedEvents() override;

    private:
        int listenerId; // This identifies which player this listener is for
        GameObject& m_Object;
    };

    class HealthListener final : public IEventListener
    {
    public:
        HealthListener() = default;
        HealthListener(GameObject& gameObj, int id) : m_Object(gameObj), listenerId(id) {}

        void OnEvent(IEvent& event) override;

        std::vector<std::type_index> GetSupportedEvents() override;

    private:
        int listenerId; // This identifies which player this listener is for
        GameObject& m_Object;
    };


    class NodeInteractorEvent;
    class CharacterDeathEvent;
    class TriangularGrid;
    class UpgradeNodeEvent;
    class NodeListener final : public IEventListener
    {
    public:
		NodeListener() = default;
		NodeListener(TriangularGrid& pGrid, int id) : listenerId(id), pointsGain(25), m_pGrid(pGrid){}

        void OnEvent(IEvent& event) override;

        std::vector<std::type_index> GetSupportedEvents() override;

    private:
        void OnNodeEventPlayer(NodeInteractorEvent& event);
        void OnNodeEventEnemy(NodeInteractorEvent& event);
        void OnNodeEventCoily(NodeInteractorEvent& event);

        void OnDeathEventQBert(CharacterDeathEvent& event);
        void OnDeathEventCoily(CharacterDeathEvent& event);
        void OnDeathEvent(CharacterDeathEvent& event);

        void OnNodeUpgradedEvent(UpgradeNodeEvent& event);

        TriangularGrid& m_pGrid;
        int listenerId; // This identifies which player this listener is for
        int pointsGain;
    };

    class EggListener final : public IEventListener
    {
    public:
        EggListener() = default;
		EggListener(int id) : listenerId(id) {}

        void OnEvent(IEvent& event) override;

        std::vector<std::type_index> GetSupportedEvents() override;

    private:
        int listenerId;
    };

    class EnemyManager;
    class EraseOneEnemyEvent;
    class EraseAllEnemiesEvent;
    class EnemyListener final : public IEventListener
    {
    public:
		EnemyListener() = default;
        EnemyListener(EnemyManager* enemyManager) : m_EnemyManager(enemyManager) {}
		void OnEvent(IEvent& event) override;
		std::vector<std::type_index> GetSupportedEvents() override;

    private:
		
        void OnEnemyDeathEvent(EraseOneEnemyEvent& event);
        void OnAllEnemiesDeathEvent(EraseAllEnemiesEvent& event);
       
        EnemyManager* m_EnemyManager;
    };

    

}

