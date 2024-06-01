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
		//std::unique_ptr<Audio> audio = std::make_unique<Audio>();
		std::unique_ptr<NullAudio> audio = std::make_unique<NullAudio>();

		ServiceLocator::RegisterAudioService(std::move(audio));
		//ServiceLocator::RegisterService(dae::ServiceType::Audio, std::move(audio));
	}
}
