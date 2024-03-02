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
		FPSComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> pFont/*, int posX, int posY, int posZ = 1*/);
		~FPSComponent();
		void Render() const;
		void Update(float elasped);

		float m_Number{ 0 };
		int m_CountFPS{ 0 };
		float m_AccumulatedTime{ 0 };

		std::vector<float> m_FrameRateVector{};

		const size_t m_MaxFrameSamples = 50;
	};

}

