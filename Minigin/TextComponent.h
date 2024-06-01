#pragma once
#include "BaseComponent.h" // Include the BaseComponent header
#include "TextureComponent.h"
#include <string>
#include <memory>
#include "Transform.h"
#include <glm/glm.hpp>

struct _TTF_Font;
namespace dae
{ 
	//class Font;
	class Texture2D;

	class TextComponent : public BaseComponent
	{
	public:
		//TextComponent(std::unique_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> pFont/*, int posX, int posY, int posZ = 1 */);
		TextComponent(GameObject& pOwner, const std::string& text, _TTF_Font* pFont);

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
		std::string m_Text;
		_TTF_Font* m_Font;
		bool m_needsUpdate;

	};

}

