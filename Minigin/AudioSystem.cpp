#include "AudioSystem.h"
#include <iostream>
#include "SDL_mixer.h"
#include "SDL.h"
#include "ResourceManager.h"




namespace dae
{ 
	class Audio::SDL_AudioImpl
	{
	public:
		SDL_AudioImpl()	
		{
			Mix_Init(MIX_INIT_MP3);
			Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
		}

		~SDL_AudioImpl() 
		{
			Mix_CloseAudio();
			Mix_Quit();
		}

		void Play(sound_id soundId, const float volume, bool looping = 0) const
		{
			volume;
			int loop = looping ? -1 : 0; // SDL_mixer uses -1 for infinite looping
			Mix_Chunk* sound = ResourceManager::GetInstance().GetSound(soundId);
			if (sound)
			{
				int channel = Mix_PlayChannel(-1, sound, loop); // -1 means the first available channel
				if (channel != -1) 
				{
					Mix_Volume(channel, static_cast<int>(m_CurrentVolume * MIX_MAX_VOLUME)); // Scale volume to SDL_mixer range
					ResourceManager::GetInstance().SetChannel(soundId, channel);
				}
			}
		}

		void StopSound(sound_id soundId) const
		{
			int channel = ResourceManager::GetInstance().GetChannel(soundId);
			if (channel != -1) {
				Mix_HaltChannel(channel);
			}
		}

		void SetVolume(float volume)
		{
			m_CurrentVolume += volume;
			if (m_CurrentVolume < 0)
				m_CurrentVolume = 0;
			if (m_CurrentVolume > 1)
				m_CurrentVolume = 1;
	
			Mix_Volume(-1, static_cast<int>(m_CurrentVolume * MIX_MAX_VOLUME)); // Set volume for all channels
		}

		void Mute()
		{
			m_IsSoundOn = !m_IsSoundOn;
			Mix_Volume(-1, static_cast<int>(m_IsSoundOn * MIX_MAX_VOLUME)); // Set volume for all channels
		}

		void StopAll()
		{
			Mix_HaltChannel(-1); // Stops all channels (when it goes into menu for example, or pause)
		}

	private:
		bool m_IsSoundOn{ true };
		float m_CurrentVolume{ 1.0f };
	};



	IAudio::~IAudio()
	{
	}

	Audio::Audio()
	{
		if (!pImpl.get())
			pImpl = std::make_unique<SDL_AudioImpl>();

		m_IsRunning = true;
		m_Thread = std::jthread(&dae::Audio::ProcessQueue, this);
	}

	Audio::~Audio()
	{
		// Signal the thread to stop running.
		{
			std::lock_guard<std::mutex> lock(m_Mutex);
			m_IsRunning = false;
			m_Cond.notify_one(); // Ensure to wake up the thread if it's waiting.
		}

		// Wait for the thread to finish.
		if (m_Thread.joinable())
			m_Thread.join();
	}

	void Audio::PlaySound(sound_id soundId, const float volume, bool looping)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_Action.push([this, soundId, volume, looping]() {
			pImpl->Play(soundId, volume, looping);
			});
		m_Cond.notify_one();
	}

	void Audio::SetVolume(const float volume)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_Action.push([this, volume]() {
			pImpl->SetVolume(volume);
			});
		m_Cond.notify_one();
	}

	void Audio::Mute()
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_Action.push([this]() {
			pImpl->Mute();
			});
		m_Cond.notify_one();
	}

	void Audio::StopSound(sound_id soundId)
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_Action.push([this, soundId]() {
			pImpl->StopSound(soundId);
			});
		m_Cond.notify_one();
	}

	void Audio::StopAll()
	{
		std::lock_guard<std::mutex> lock(m_Mutex);
		m_Action.push([this]() {
			pImpl->StopAll();
			});
		m_Cond.notify_one();
	}

	void Audio::ProcessQueue()
	{
		std::unique_lock<std::mutex> lock(m_Mutex);
		while (m_IsRunning)
		{
			//m_Cond.wait(lock, [this]() { return !m_Action.empty(); });
			
			// Wait until there is an action to process or the thread needs to stop running.
			m_Cond.wait(lock, [this]() { return !m_Action.empty() || !m_IsRunning; });

			// Exit the loop if the thread is no longer running and there are no actions to process.
			if (!m_IsRunning && m_Action.empty()) break;

			if (!m_Action.empty())
			{
				auto task = std::move(m_Action.front());
				m_Action.pop();
				lock.unlock();  // Unlock the mutex while the task is being processed.
				task();
				lock.lock();    // Re-lock the mutex after task completion.
			}
		}
	}


	void NullAudio::PlaySound(sound_id soundId, const float volume, bool looping)
	{
		soundId;
		volume;
		looping;
	}

	void NullAudio::SetVolume(const float volume)
	{
		volume;
	}

	void NullAudio::Mute()
	{
	}

	void NullAudio::StopAll()
	{
	}

	void NullAudio::StopSound(sound_id soundId)
	{
		soundId;
	}


	LoggerAudio::LoggerAudio(std::unique_ptr<IAudio>&& pAudioReal)
		: m_pAudioReal(std::move(pAudioReal))
	{
	}

	void LoggerAudio::PlaySound(sound_id soundId, const float volume, bool looping)
	{
		m_pAudioReal->PlaySound(soundId, volume, looping);
		std::cout << "Sound played: " << soundId << std::endl;
	}

	void LoggerAudio::SetVolume(const float volume)
	{
		m_pAudioReal->SetVolume(volume);
		std::cout << "Volume set to: " << volume << std::endl;
	}

	void LoggerAudio::Mute()
	{
		m_pAudioReal->Mute();
		std::cout << "Sound Mute state changed" << std::endl;
	}


	void LoggerAudio::StopAll()
	{
		m_pAudioReal->StopAll();
		std::cout << "All sounds stopped" << std::endl;
	}


	void LoggerAudio::StopSound(sound_id soundId)
	{
		m_pAudioReal->StopSound(soundId);
		std::cout << "Sound stopped" << std::endl;
	}

}

