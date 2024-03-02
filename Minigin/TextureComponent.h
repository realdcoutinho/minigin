#pragma once
#include "BaseComponent.h" // Include the BaseComponent header
#include <glm/vec2.hpp>
#include <string>

struct SDL_Texture;
namespace dae
{
	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent(std::shared_ptr<GameObject> pOwner, const std::string& filename);
		TextureComponent(GameObject* pOwner, SDL_Texture* texture);
		~TextureComponent();

		TextureComponent(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator= (const TextureComponent&) = delete;
		TextureComponent& operator= (const TextureComponent&&) = delete;

		void Render() const override;
		void Update(float elapsed) override;

		glm::ivec2 GetSize() const;
		SDL_Texture* GetSDLTexture() const;

	private:
		SDL_Texture* m_texture;
	};
}


