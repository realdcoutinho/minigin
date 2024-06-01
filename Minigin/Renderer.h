#pragma once
#include <SDL.h>
#include "Singleton.h"
#include "imgui_dae.h"
#include <glm/vec2.hpp>
#include <memory>

namespace dae
{
	class imgui_dae;
	class TextureComponent;
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
		SDL_Renderer* m_renderer{};
		SDL_Window* m_window{};
		SDL_Color m_clearColor{};	
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		//void RenderTexture(const Texture2D& texture, float x, float y) const;
		//void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		void RenderTexture(TextureComponent* texture, float x, float y) const;
		void RenderTexture(SDL_Texture* texture, float x, float y) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, const glm::vec2& scale) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, int imageIndex, int segments) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, int imageIndex, int segments, const glm::vec2& scale) const;
		void RenderTexture(SDL_Texture* texture, float x, float y, glm::vec2 indexPos, glm::vec2 segmentSize, const glm::vec2& scale) const;


		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_clearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_clearColor = color; }


		std::unique_ptr<imgui_dae> m_myGui{};
	};
}

