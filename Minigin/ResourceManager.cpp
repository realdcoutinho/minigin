#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include <stdexcept>

#include "SDL_render.h"

void dae::ResourceManager::Init(const std::string& dataPath)
{
	m_dataPath = dataPath;

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

SDL_Texture* dae::ResourceManager::LoadTexture(const std::string& file)
{
	const auto fullPath = m_dataPath + file;
	SDL_Texture* texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	m_TexturesMap[file] = texture;
	return texture;
}

_TTF_Font* dae::ResourceManager::GetFont(const std::string& name, unsigned int size)
{
	if (m_FontMap.contains(name))
		return m_FontMap.at(name);
	else
		return LoadFont(name, size);

}

_TTF_Font* dae::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	std::string fullPath = m_dataPath + file;
	auto font = TTF_OpenFont(fullPath.c_str(), size);
	if (font == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
	return font;
}

SDL_Texture* dae::ResourceManager::GetTexture(const std::string& name)
{
	if (m_TexturesMap.contains(name))
		return m_TexturesMap.at(name);
	else
		return LoadTexture(name);
}


void dae::ResourceManager::SetChannel(unsigned short id, int channel) 
{
	m_ChannelMap[id] = channel;
}

int dae::ResourceManager::GetChannel(unsigned short id) 
{
	auto it = m_ChannelMap.find(id);
	if (it != m_ChannelMap.end()) {
		return it->second;
	}
	return -1; // Return -1 if the sound ID is not associated with any channel
}

Mix_Chunk* dae::ResourceManager::LoadSound(const std::string& file)
{
	if (m_FileToIdMap.find(file) == m_FileToIdMap.end()) 
	{ // Only load if not already loaded
		std::string fullPath = m_dataPath + file;
		auto sound = Mix_LoadWAV(fullPath.c_str());
		if (sound) 
		{
			currentSoundId++;
			m_SoundMap[currentSoundId] = sound;
			m_FileToIdMap[file] = currentSoundId;  // Map the file to the new sound ID
			return sound;
		}
	}
	return nullptr;
}

Mix_Chunk* dae::ResourceManager::GetSound(unsigned short id) {
	
	auto it = m_SoundMap.find(id);
	
	if (it != m_SoundMap.end()) 
	{
		return it->second;
	}
	return nullptr; // Sound ID not found
}

Mix_Chunk* dae::ResourceManager::GetSound(const std::string& file) 
{
	auto it = m_FileToIdMap.find(file);

	if (it != m_FileToIdMap.end()) 
	{
		// File is known, retrieve using ID
		return m_SoundMap[it->second];
	}
	else 
	{
		// File is not known, load and store it
		auto sound = LoadSound(file);
		if (sound) 
		{
			return sound;
		}
	}
	return nullptr; // File could not be loaded
}