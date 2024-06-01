#include "TextComponent.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "GameObject.h"


namespace dae
{
	//dae::TextComponent::TextComponent(std::unique_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> pFont/*, int posX, int posY, int posZ*/)
	//	: BaseComponent(pOwner.get()),
	//	m_Font{ std::move(pFont) }
	//	, m_Text{ text }
	//	, m_needsUpdate(true)
	//{
	//}

	dae::TextComponent::TextComponent(GameObject& pOwner, const std::string& text, _TTF_Font* pFont/*, int posX, int posY, int posZ = 1 */)
		: BaseComponent(pOwner)
		, m_Font{ pFont }
		, m_Text{ text }
		, m_needsUpdate(true)
	{
	}

	TextComponent::~TextComponent()
	{
	}

	TextComponent* TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_needsUpdate = true;
		return this;
	}

	void TextComponent::Render()
	{

		if (GetOwner() == nullptr)
			return;

		if (m_texture != nullptr)
		{

			const float x = GetOwner()->GetWorldPosition().x;
			const float y = GetOwner()->GetWorldPosition().y;
			Renderer::GetInstance().RenderTexture(m_texture.get(), x, y);
		}
	}

	void TextComponent::Update()
	{
		if (m_needsUpdate)
		{
			const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
			const auto surf = TTF_RenderText_Blended(m_Font, m_Text.c_str(), color);
			if (surf == nullptr)
			{
				throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
			}
			auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
			if (texture == nullptr)
			{
				throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
			}
			SDL_FreeSurface(surf);
			m_texture = std::make_shared<TextureComponent>(*GetOwner(), texture);
			m_needsUpdate = false;
		}
	}
}
