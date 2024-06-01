#include "TextureComponent.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"


//dae::TextureComponent::TextureComponent(std::unique_ptr<GameObject> pOwner, const std::string& filename)
//	: BaseComponent(pOwner.get())
//{
//	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
//	//pOwner->AddComponent(std::move(this));
//}

dae::TextureComponent::TextureComponent(GameObject& pOwner, const std::string& filename, int segments)
	: BaseComponent(pOwner),
	m_texture(ResourceManager::GetInstance().GetTexture(filename)),
	m_Segments(segments)
	, m_CurrentSegment(0)
	, m_Scale({ 1.0f, 1.0f })
{

}

dae::TextureComponent::TextureComponent(GameObject& pOwner, SDL_Texture* texture, int segments)
	: BaseComponent(pOwner),
	m_texture(texture),
	m_Segments(segments),
	m_CurrentSegment(0)
	, m_Scale({ 1.0f, 1.0f })
{
}

dae::TextureComponent::TextureComponent(GameObject& pOwner)
	: BaseComponent(pOwner)
	, m_Scale({1.0f, 1.0f})
{
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

void dae::TextureComponent::Render()
{
	if (GetOwner() == nullptr)
		return;
	if (m_texture != nullptr)
	{
		if(m_CanRender)
		{
			const float x = GetOwner()->GetWorldPosition().x;
			const float y = GetOwner()->GetWorldPosition().y;

			if (nodesTest)
			{
				Renderer::GetInstance().RenderTexture(m_texture, x, y, m_TexturePositionIndex, m_TextureSegments, m_Scale);
				return;
			}

			if (m_Segments > 1)
				Renderer::GetInstance().RenderTexture(m_texture, x, y, m_CurrentSegment, m_Segments, m_Scale);
			if (m_Segments == 1)
				Renderer::GetInstance().RenderTexture(m_texture, x, y, m_Scale);
		}
	}
}

void dae::TextureComponent::Update()
{

}