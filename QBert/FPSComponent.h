#pragma once
#include "TextComponent.h"
#include <string>
#include <memory>
#include "GameObject.h"
#include "BaseComponent.h"
#include "Transform.h"
#include <memory>
#include <queue>
#include <vector>

namespace dae
{
	class TextComponent;

	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(GameObject& pOwner);

		~FPSComponent();
		void Render() override;
		void Update() override;

	private:
		std::vector<float> m_FrameRateVector{};

		TextComponent* m_TextComponent;
		const size_t m_MaxFrameSamples = 50;
		float m_Number{ 0 };
		int m_CountFPS{ 0 };
		float m_AccumulatedTime{ 0 };
	};

}
