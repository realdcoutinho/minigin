#pragma once
#include <unordered_map>
#include "Singleton.h"
#include <memory>
#include <string>

namespace dae
{
	struct SDL_Texture;

	class TextureManager final : public Singleton<TextureManager>
	{
	public:

		SDL_Texture* GetTexturePointer(const std::string& name);

	private:

		friend class Singleton<TextureManager>;
		TextureManager() = default;
		SDL_Texture* InitializeTexture(const std::string& name);

		std::unordered_map<std::string, std::unique_ptr<SDL_Texture>> m_TexturesMap;
	};
}
