#pragma once
#include "BaseComponent.h" // Include the BaseComponent header
#include "TextureComponent.h"
#include <string>
#include <memory>
#include "Transform.h"
#include <glm/glm.hpp>

#include "SDL.h"
#include "SDL_ttf.h"

struct _TTF_Font;
namespace dae
{ 
	//class Font;
	class Texture2D;

	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(GameObject& pOwner, const std::string& text, _TTF_Font* pFont, const SDL_Color& color = { 255, 255, 255, 255 });

		~TextComponent();

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void Render() override;
		void Update() override;

		TextComponent* SetText(const std::string& text);


	protected:

		std::shared_ptr<TextureComponent> m_texture;

	private:
		 const SDL_Color m_TextColor;
		std::string m_Text;
		_TTF_Font* m_Font;
		bool m_needsUpdate;

	};

}

