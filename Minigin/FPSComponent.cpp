#include "FPSComponent.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include <chrono>
#include <queue>
#include <iomanip> // For std::fixed and std::setprecision
#include <sstream> // Include stringstream
#include <iostream>
#include <numeric> // For std::accumulate

namespace dae
{
	FPSComponent::FPSComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> pFont/*, int posX, int posY, int posZ*/)
		: TextComponent(pOwner, text, pFont/*, posX, posY*/)
	{
		/*posZ++;*/
	}
	FPSComponent::~FPSComponent()
	{
		//delete m_texture;
	}

	void FPSComponent::Render() const
	{
		if (m_texture != nullptr)
		{
			//const auto& pos = m_Transform.GetPosition();
			Renderer::GetInstance().RenderTexture(m_texture.get(), GetOwner()->GetWorldPosition().x, GetOwner()->GetWorldPosition().y);
		}
	}

	void FPSComponent::Update(float elasped)
	{
		TextComponent::Update(elasped);

		/// Update the queue of frame times
			if (m_FrameRateVector.size() >= m_MaxFrameSamples)
			{
				m_FrameRateVector.erase(m_FrameRateVector.begin()); // Remove the oldest frame time
			}
			m_FrameRateVector.emplace_back(elasped); // Add the new frame time

		m_AccumulatedTime += elasped;

		// Update the FPS display every 0.15 seconds
		if (m_AccumulatedTime > 0.15f)
		{
			// Calculate the average frame time
			float sum = std::accumulate(m_FrameRateVector.begin(), m_FrameRateVector.end(), 0.0f);
			float averageFrameTime = sum / m_FrameRateVector.size();

			// Compute FPS from the average frame time
			float averageFPS = 1.0f / averageFrameTime;

			// Format and set the FPS text
			std::stringstream stream;
			stream << std::fixed << std::setprecision(1) << averageFPS;
			std::string fpsText = stream.str() + " FPS";
			SetText(fpsText);

			m_AccumulatedTime = 0.0f;
		}
	}
}

