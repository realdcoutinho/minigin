#include "ServicesLoader.h"
#include "ServiceLocator.h"
#include "AudioSystem.h"

namespace dae
{
	ServicesLoader::ServicesLoader()
	{
		LoadServices();
	}
	void ServicesLoader::LoadServices()
	{
		LoadAudioService();
	}
	void ServicesLoader::LoadAudioService()
	{
		ServiceLocator::Initialize();
		std::unique_ptr<Audio> audio = std::make_unique<Audio>();

		ServiceLocator::RegisterAudioService(std::move(audio));
	}
}
