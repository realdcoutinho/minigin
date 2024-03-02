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
	dae::TextComponent::TextComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> pFont/*, int posX, int posY, int posZ*/)
		: BaseComponent(pOwner),
		m_Font{ std::move(pFont) }
		, m_Text{ text }
		, m_needsUpdate(true)
		//create texture
	{
		//m_texture = new TextureComponent(m_pOwner, "text.tga");
	}

	//dae::TextComponent::TextComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> pFont/*, glm::vec3& pos*/)
	//	:BaseComponent(pOwner),
	//	m_Font{ std::move(pFont) }
	//	, m_Text{ text }
	//	//, m_Positon{ pos}
	//	, m_TextTexture(nullptr)
	//	, m_needsUpdate(true)
	//	//create texture
	//{
	//}

	TextComponent::~TextComponent()
	{
		//delete m_texture;
	}


	TextComponent* TextComponent::SetText(const std::string& text)
	{
		m_Text = text;
		m_needsUpdate = true;
		return this;
	}

	void TextComponent::Render() const
	{

		if (m_pOwner == nullptr)
			return;
		//auto owner = GetOwner();
		//m_pOwner
		if (m_texture != nullptr)
		{

			const float x = m_pOwner->GetWorldPosition().x;
			const float y = m_pOwner->GetWorldPosition().y;
			//const auto& pos = m_Transform.GetPosition();
			Renderer::GetInstance().RenderTexture(m_texture.get(), x, y);
		}

		
	}

	void TextComponent::Update(float elapsed)
	{
		if (m_needsUpdate)
		{
			const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
			const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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
			//m_TextTexture = std::make_shared<Texture2D>(texture);
			m_texture = std::make_shared<TextureComponent>(m_pOwner, texture);
			m_needsUpdate = false;
		}
		elapsed;
	}
}
