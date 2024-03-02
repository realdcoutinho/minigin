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
		//TextComponent(std::shared_ptr<GameObject> pOwner, const std::string& text, std::shared_ptr<Font> pFont/*, glm::vec3& pos*/);
		~TextComponent();


		//void SetGameObject(GameObject* pGameObject) override {
		//	//m_pGameObject = pGameObject;
		//	// Additional implementation if needed
		//}

		//GameObject* GetGameObject() override {
		//	return m_pGameObject;
		//}


		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		TextComponent* SetText(const std::string& text);
		//void SetPosition(const float x, const float y);
		//TextComponent* SetFont(std::shared_ptr<Font> pFont);

		void Render() const override;
		void Update(float elapsed) ;

		std::string m_Text;
		std::shared_ptr<Font> m_Font;


		bool m_needsUpdate;
		//std::shared_ptr<Texture2D> m_TextTexture;
		std::shared_ptr<TextureComponent> m_texture;

	};

}

