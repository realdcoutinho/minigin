#pragma once
#include "BaseComponent.h" // Include the BaseComponent header
#include "TextureComponent.h"
#include <string>
#include <memory>
#include "Transform.h"
#include <glm/glm.hpp>

namespace dae
{ 
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> pFont/*, int posX, int posY, int posZ = 1 */);
		~TextComponent();

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		void Render() const override;
		void Update(float elapsed) override;

	protected:

		TextComponent* SetText(const std::string& text);
		std::shared_ptr<TextureComponent> m_texture;

	private:
		std::string m_Text;
		std::shared_ptr<Font> m_Font;
		bool m_needsUpdate;

	};

}

