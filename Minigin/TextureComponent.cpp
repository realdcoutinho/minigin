#include "TextureComponent.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"


dae::TextureComponent::TextureComponent(std::shared_ptr<GameObject> pOwner, const std::string& filename)
	: BaseComponent(pOwner)
{
	filename;
	m_texture = ResourceManager::GetInstance().LoadTextureP(filename);
}

dae::TextureComponent::TextureComponent(GameObject* pOwner, SDL_Texture* texture)
	: BaseComponent(pOwner)
{
	m_texture = texture;
}

dae::TextureComponent::~TextureComponent()
{
	SDL_DestroyTexture(m_texture);
}

glm::ivec2 dae::TextureComponent::GetSize() const
{
	SDL_Rect dst;
	SDL_QueryTexture(GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	return { dst.w,dst.h };
}

SDL_Texture* dae::TextureComponent::GetSDLTexture() const
{
	return m_texture;
}

void dae::TextureComponent::Render() const
{

	if (GetOwner() == nullptr)
		return;
	auto owner = GetOwner();
	if (m_texture != nullptr)
	{

		const float x = owner->GetWorldPosition().x;
		const float y = owner->GetWorldPosition().y;
		Renderer::GetInstance().RenderTexture(m_texture, x, y);
	}



}

void dae::TextureComponent::Update(float elapsed)
{
	//if (m_needsUpdate)
	//{
	//	const SDL_Color color = { 255,255,255,255 }; // only white text is supported now
	//	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
	//	if (surf == nullptr)
	//	{
	//		throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
	//	}
	//	auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
	//	if (texture == nullptr)
	//	{
	//		throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
	//	}
	//	SDL_FreeSurface(surf);
	//	m_TextTexture = std::make_shared<Texture2D>(texture);
	//	m_needsUpdate = false;
	//}
	elapsed;
}