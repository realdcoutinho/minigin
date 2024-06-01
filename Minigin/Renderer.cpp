#include <stdexcept>
#include "Renderer.h"
#include "TextureComponent.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "imgui_plot.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl2.h"
#include "implot.h"
#include "imgui_dae.h"
#include "Renderer.h"
#include "Scene.h"


int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();


	//m_myGui = std::make_unique<imgui_dae>();
	//m_myGui->Init(window, SDL_GL_GetCurrentContext());
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	SceneManager::GetInstance().Render();



	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{

	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(TextureComponent* texture, float x, float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture->GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture->GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, float x, float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);

	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, float x, float y, const glm::vec2& scale) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture, nullptr, nullptr, &dst.w, &dst.h);
	dst.w *= static_cast<int>(scale.x);
	dst.h *= static_cast<int>(scale.y);
	SDL_RenderCopy(GetSDLRenderer(), texture, nullptr, &dst);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, float x, float y, int imageIndex, int segments) const
{


	SDL_Rect src{};
	SDL_Rect dst{};
	int texW = 0, texH = 0;

	// Query the texture to get its full width and height
	SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);

	// Calculate the width of each image in the texture
	int imageWidth = texW / segments;

	// Set up the source rectangle with the position and size of the desired image
	src.x = imageWidth * imageIndex;  // Move the source rectangle based on the image index
	src.y = 0;
	src.w = imageWidth;
	src.h = texH;

	// Set up the destination rectangle where the image will be drawn on the screen
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = imageWidth;  // Use the individual image width for the destination rectangle
	dst.h = texH;

	// Render the specific part of the texture
	SDL_RenderCopy(GetSDLRenderer(), texture, &src, &dst);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, float x, float y, int imageIndex, int segments, const glm::vec2& scale) const
{
	SDL_Rect src{};
	SDL_Rect dst{};
	int texW = 0, texH = 0;

	// Query the texture to get its full width and height
	SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);

	// Calculate the width of each image in the texture
	int imageWidth = texW / segments;
	int imageHeight = texH;

	// Set up the source rectangle with the position and size of the desired image
	src.x = imageWidth * imageIndex;
	src.y = 0;
	src.w = imageWidth;
	src.h = imageHeight;

	// Set up the destination rectangle where the image will be drawn on the screen
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(imageWidth * scale.x);  // Scale the width of the destination rectangle
	dst.h = static_cast<int>(imageHeight * scale.y); // Scale the height of the destination rectangle

	// Render the specific part of the texture
	SDL_RenderCopy(GetSDLRenderer(), texture, &src, &dst);
}

void dae::Renderer::RenderTexture(SDL_Texture* texture, float x, float y, glm::vec2 indexPos, glm::vec2 segmentSize, const glm::vec2& scale) const
{
	SDL_Rect src{};
	SDL_Rect dst{};
	int texW = 0, texH = 0;

	// Query the texture to get its full width and height
	SDL_QueryTexture(texture, nullptr, nullptr, &texW, &texH);

	// Calculate the width of each image in the texture
	int imageWidth = texW / static_cast<int>(segmentSize.x);
	int imageHeight = texH / static_cast<int>(segmentSize.y);

	// Set up the source rectangle with the position and size of the desired image
	src.x = imageWidth * static_cast<int>(indexPos.x);
	src.y = imageHeight * static_cast<int>(indexPos.y);
	src.w = imageWidth;
	src.h = imageHeight;

	// Set up the destination rectangle where the image will be drawn on the screen
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(imageWidth * scale.x);  // Scale the width of the destination rectangle
	dst.h = static_cast<int>(imageHeight * scale.y); // Scale the height of the destination rectangle

	// Render the specific part of the texture
	SDL_RenderCopy(GetSDLRenderer(), texture, &src, &dst);
}


SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }


//void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
//{
//	SDL_Rect dst{};
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
//}
//
//void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
//{
//	SDL_Rect dst{};
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	dst.w = static_cast<int>(width);
//	dst.h = static_cast<int>(height);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
//}