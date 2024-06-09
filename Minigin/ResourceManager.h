#pragma once
#include <string>
#include <memory>
#include "Singleton.h"
//#include <SDL_image.h>
#include <SDL.h>
#include <unordered_map>
#include <SDL_mixer.h>
#include <memory>
#include <IServices.h>


struct _TTF_Font;
namespace dae
{
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		//std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int size) const;

		//~ResourceManager();
		SDL_Texture* GetTexture(const std::string& name);
		_TTF_Font* GetFont(const std::string& name, unsigned int size);
		

		Mix_Chunk* GetSound(unsigned short id);
		Mix_Chunk* GetSound(const std::string& file);

		void FreeAllSoundsSound();
		int GetChannel(unsigned short id);
		void SetChannel(unsigned short id, int channel);


		//std::shared_ptr<Texture2D> LoadTexture(const std::string& file) const;

	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::string m_dataPath;

		SDL_Texture* LoadTexture(const std::string& file);
		std::unordered_map<std::string, SDL_Texture*> m_TexturesMap;

		_TTF_Font* LoadFont(const std::string& file, unsigned int size);
		std::unordered_map<std::string, _TTF_Font*> m_FontMap;

		Mix_Chunk* LoadSound(const std::string& file);
		std::unordered_map<std::string, unsigned short> m_FileToIdMap; // Maps filenames to sound IDs


		std::unordered_map<unsigned short, Mix_Chunk*> m_SoundMap{};
		std::unordered_map<unsigned short, int> m_ChannelMap{};
		unsigned short currentSoundId{ 0 };
	};
}
