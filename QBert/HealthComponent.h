#pragma once
#include "BaseComponent.h"
#include "BaseEvent.h"

namespace dae
{
	class IObserver;
	class HealthComponent : public BaseComponent
	{
	public:
		HealthComponent(GameObject& pOwner, int initialHealht);
		~HealthComponent();

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) noexcept = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

		void Render() override;
		void Update() override;

		void TakeHit();
		void Respawn(int idx);
		int GetHealth() const;

	private:
		int m_Health{};
	};

}

class HealthComponent
{
};

