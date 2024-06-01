#include "ServiceLocator.h"
#include "ResourceManager.h"
#include <iostream>

namespace dae
{
	void ServiceLocator::Initialize()
	{
		m_pAudioService = std::make_unique<NullAudio>();

		//m_NullServices[ServiceType::Audio] = std::make_unique<NullAudio>();
		//m_NullServices[ServiceType::Video] = nullptr;
		//m_NullServices[ServiceType::Physics] = nullptr;
		//m_NullServices[ServiceType::Renderer] = nullptr;
		//m_NullServices[ServiceType::SceneManager] = nullptr;
		//m_NullServices[ServiceType::InputManager] = nullptr;
		//m_NullServices[ServiceType::ResourceManager] = std::make_unique<NullResource>();


	}
	
	std::unique_ptr<IAudio> ServiceLocator::m_pAudioService = nullptr;
	void ServiceLocator::RegisterAudioService(std::unique_ptr<IAudio> pService)
	{ 
		if (m_pAudioService == nullptr)
		{
			m_pAudioService = std::move(m_pAudioService);
		}
		else
		{
			m_pAudioService = std::move(pService);
		}
	}

	std::unique_ptr<IAudio>& ServiceLocator::GetAudioService()
	{
		return m_pAudioService;
	}
}