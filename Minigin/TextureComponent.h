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
		//TextureComponent(std::unique_ptr<GameObject> pOwner, const std::string& filename);
		TextureComponent(GameObject& pOwner, const std::string& filename, int segments = 1);
		TextureComponent(GameObject& pOwner, SDL_Texture* texture, int segments = 1);
		TextureComponent(GameObject& pOwner);
		~TextureComponent();

		TextureComponent(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&&) = delete;
		TextureComponent& operator= (const TextureComponent&) = delete;
		TextureComponent& operator= (const TextureComponent&&) = delete;

		void Render() override;
		void Update() override;

		glm::ivec2 GetSize() const;
		SDL_Texture* GetSDLTexture() const;

		void SetTexture(SDL_Texture* texture, int segments) 
		{ 
			m_texture = texture; 
			m_Segments = segments;
		}
		void SetTexture(SDL_Texture* texture) { m_texture = texture; }
		void SetSegments(int curSegment) { m_CurrentSegment = curSegment; }

		void SetScale(const glm::vec2& scale) { m_Scale = scale; }

		bool nodesTest = false;
		void SetTexturePositionIndex(const glm::vec2& index) { m_TexturePositionIndex = index; }
		void SetTextureSegments(const glm::vec2& segments) { m_TextureSegments = segments; }
		void SetTextureSegmentsY(int segments) { m_TexturePositionIndex.y = static_cast<float>(segments); }

		void SetRender(bool canRender) { m_CanRender = canRender; }

	private:
		SDL_Texture* m_texture;
		int m_Segments;
		int m_CurrentSegment{ 0 };
		glm::vec2 m_Scale{ 1,1 };
		glm::vec2 m_TexturePositionIndex{ 0,0 };
		glm::vec2 m_TextureSegments{ 1,1 };
		bool m_CanRender{ true };
	};
}


