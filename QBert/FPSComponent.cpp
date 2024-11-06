#include "FPSComponent.h"
#include "Renderer.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include <chrono>
#include <queue>
#include <iomanip> // For std::fixed and std::setprecision
#include <sstream> // Include stringstream
#include <iostream>
#include <numeric> // For std::accumulate
#include <memory>
#include "TimeManager.h"

namespace dae
{
	FPSComponent::FPSComponent(GameObject& pOwner)
		: BaseComponent(pOwner)
	{
		std::unique_ptr<TextComponent> component = std::make_unique<TextComponent>(pOwner, "0 FPS", ResourceManager::GetInstance().GetFont("Lingua.otf", 36));
		m_TextComponent = component.get();
		GetOwner()->AddComponent(std::move(component));
	}

	FPSComponent::~FPSComponent()
	{
	}

	void FPSComponent::Render()
	{
	}

	void FPSComponent::Update()
	{
		//TextComponent::Update(elasped);
		float elapsed = TimeManager::GetInstance().GetElapsed();


		if (m_FrameRateVector.size() >= m_MaxFrameSamples)
		{
			m_FrameRateVector.erase(m_FrameRateVector.begin()); // Remove the oldest frame time
		}
		m_FrameRateVector.emplace_back(elapsed); // Add the new frame time

		m_AccumulatedTime += elapsed;

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
			m_TextComponent->SetText(fpsText);

			m_AccumulatedTime = 0.0f;
		}
	}
}

