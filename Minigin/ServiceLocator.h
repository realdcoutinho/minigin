#pragma once
//namespace dae
//{
//	// ServiceLocator class
//	// This class is a singleton that can be used to locate services
//	// It is a singleton because we only need one instance of it
//	// It is a template class because we want to be able to use it with different types
//	template <typename T>
//}

#include "AudioSystem.h"
#include <unordered_map>
#include <memory>
#include <map>

namespace dae
{
	enum class ServiceType
	{
		Audio,
		Video,
		Physics,
		Renderer,
		SceneManager,
		InputManager,
		ResourceManager,
	};

	class ServiceLocator final
	{
	public:
		ServiceLocator(const ServiceLocator& other) = delete;
		ServiceLocator(ServiceLocator&& other) = delete;
		ServiceLocator& operator=(const ServiceLocator& other) = delete;
		ServiceLocator& operator=(ServiceLocator&& other) = delete;
		ServiceLocator() = default;
		~ServiceLocator() = default;

		static void Initialize();

		static void RegisterAudioService(std::unique_ptr<IAudio> pService);
		static std::unique_ptr<IAudio>& GetAudioService();


	private:
			static std::unique_ptr<IAudio> m_pAudioService;
			static NullAudio m_pAudioServiceNull;
	};
}


