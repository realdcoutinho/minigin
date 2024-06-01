#pragma once
#include "BaseComponent.h"
namespace dae
{
	class RespawnComponent final : public BaseComponent
	{
	public:
		RespawnComponent(GameObject& pOwner);
		~RespawnComponent() = default;
		RespawnComponent(const RespawnComponent&) = delete;
		RespawnComponent(RespawnComponent&&) = delete;
		RespawnComponent& operator= (const RespawnComponent&) = delete;
		RespawnComponent& operator= (const RespawnComponent&&) = delete;
		void Render() override;
		void Update() override;
		void OnRespawn(int idx);
		bool IsRespawning() const { return m_IsRespawning; }

	private:
		bool m_IsRespawning = false;
		float m_RespawnTimer = 2.0f;
		float m_CurrentRespawnTime = 0.0f;
		int m_RespawnIndex = 0;
		bool m_DoOnde = false;

	};
}



