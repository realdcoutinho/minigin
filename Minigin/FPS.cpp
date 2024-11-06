//#include "FPS.h"
//#include "TextComponent.h"
//#include "ResourceManager.h"
//#include <chrono>
//#include <queue>
//#include <iomanip> // For std::fixed and std::setprecision
//#include <sstream> // Include stringstream
//
//
//
//#include <iostream>
//
//namespace dae 
//{
//	FPS::FPS()
//	{
//		std::cout << "FPS INITIALIZED" << std::endl;
//		std::string text = "Hello, World!";
//		auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);		
//		const int posX = 216;
//		const int posY = 100;
//
//		// Initialize using `new`
//		m_FpsCounter = std::make_unique<TextComponent>(text, font, posX, posY, 1);
//		m_FpsCounter->SetPosition(posX, posY);
//	}
//
//	void FPS::Render() const
//	{
//		m_FpsCounter->Render();
//	}
//
//	void FPS::Update(float elasped)
//	{
//		m_AccumulatedTime += elasped;
//		if (m_AccumulatedTime > 0.15f)
//		{
//			float frameRate = 1.0f / elasped;
//			
//			// Use stringstream to format the frameRate
//			std::stringstream stream;
//			stream << std::fixed << std::setprecision(1) << frameRate; // Set to one decimal place
//			std::string frameRateStr = stream.str(); // Convert the formatted number to a string
//
//			std::string text = frameRateStr + " FPS";
//			
//			m_FpsCounter->SetText(text);
//			m_FpsCounter->Update(elasped);
//			m_AccumulatedTime = 0.0f;
//		}
//	}
//}
//
