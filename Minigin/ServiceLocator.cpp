#include "ServiceLocator.h"
#include "ResourceManager.h"
#include <iostream>

namespace dae
{
	void ServiceLocator::Initialize()
	{
		m_pAudioService = std::make_unique<NullAudio>();
	}
	
	std::unique_ptr<IAudio> ServiceLocator::m_pAudioService = nullptr;
	void ServiceLocator::RegisterAudioService(std::unique_ptr<IAudio> pService)
	{ 
		if (pService == nullptr)
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