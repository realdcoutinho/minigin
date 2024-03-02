#include "TextureComponent.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"


dae::TextureComponent::TextureComponent(std::shared_ptr<GameObject> pOwner, const std::string& filename)
	: BaseComponent(pOwner)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
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
	if (m_texture != nullptr)
	{
		const float x = GetOwner()->GetWorldPosition().x;
		const float y = GetOwner()->GetWorldPosition().y;
		Renderer::GetInstance().RenderTexture(m_texture, x, y);
	}
}

void dae::TextureComponent::Update(float elapsed)
{
	elapsed;
}