#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameObject;
	class DeathComponent final : public BaseComponent
	{
	public:

		DeathComponent(GameObject& pOwner);
		~DeathComponent() = default;
		DeathComponent(const DeathComponent&) = delete;
		DeathComponent(DeathComponent&&) = delete;
		DeathComponent& operator= (const DeathComponent&) = delete;
		DeathComponent& operator= (const DeathComponent&&) = delete;
		void Render() override;
		void Update() override;
		void OnDeath();
		bool IsDead() const { return m_IsDead; }

		private:
		bool m_IsDead = false;
		float m_DeathTimer = 0.5f;
		float m_CurrentDeathTime = 0.0f;
	};

}


