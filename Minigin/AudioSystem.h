#pragma once
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include <utility>
#include <queue>
#include <functional>
#include <condition_variable>
#include "IServices.h"

namespace dae
{


	using sound_id = unsigned short;
	class IAudio : public IService
	{
	public:
		virtual ~IAudio() override;
		virtual void PlaySound(sound_id soundId, const float volume, bool looping = 0) = 0;
		virtual void SetVolume(const float volume) = 0;
		virtual void Mute() = 0;
		virtual void StopAll() = 0;
		virtual void StopSound(sound_id soundId) = 0;
	};

	class Audio final : public IAudio
	{
		class SDL_AudioImpl;
	public:
		Audio();
		virtual ~Audio() override;
		Audio(const Audio& other) = delete;
		Audio(Audio&& other) = delete;
		Audio& operator=(const Audio& other) = delete;
		Audio& operator=(Audio&& other) = delete;

		virtual void PlaySound(sound_id soundId, const float volume, bool looping = 0) override;
		virtual void SetVolume(const float volume) override;
		virtual void Mute() override;
		virtual void StopAll() override;
		virtual void StopSound(sound_id soundId) override;

	private:
		void ProcessQueue();
		bool m_IsRunning{ false };
		std::queue<std::function<void()>> m_Action;
		std::unique_ptr<SDL_AudioImpl> pImpl{};
		std::mutex m_Mutex;
		std::condition_variable m_Cond;
		std::jthread m_Thread;
	};

	class NullAudio final : public IAudio
	{
	public:
		virtual void PlaySound(sound_id soundId, const float volume, bool looping = 0) override;
		virtual void SetVolume(const float volume) override;
		virtual void Mute() override;
		virtual void StopAll() override;
		virtual void StopSound(sound_id soundId) override;
	};

	class LoggerAudio final : public IAudio
	{
	public:
		LoggerAudio(std::unique_ptr<IAudio>&& pAudioReal);
		virtual ~LoggerAudio() = default;
		virtual void PlaySound(sound_id soundId, const float volume, bool looping = 0) override;
		virtual void SetVolume(const float volume) override;
		virtual void Mute() override;
		virtual void StopAll() override;
		virtual void StopSound(sound_id soundId) override;

	private:
		std::unique_ptr<IAudio> m_pAudioReal;
	};

};