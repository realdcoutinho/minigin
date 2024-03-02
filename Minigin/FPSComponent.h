#pragma once
#include "TextComponent.h"
#include <string>
#include <memory>
#include "GameObject.h"
#include "Transform.h"
#include <memory>
#include <queue>
#include <vector>

namespace dae
{
	class FPSComponent : public TextComponent
	{
	public:
		FPSComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> pFont);
		~FPSComponent();
		void Render() const override;
		void Update(float elasped) override;

	private:
		std::vector<float> m_FrameRateVector{};

		const size_t m_MaxFrameSamples = 50;
		float m_Number{ 0 };
		int m_CountFPS{ 0 };
		float m_AccumulatedTime{ 0 };
	};

}

