#include "HUDComponent.h"
#include "TextComponent.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include <sstream> // Include stringstream
#include "CharacterComponent.h"
#include "QbertEvents.h"
#include <memory>


namespace dae
{
	HUDComponent::HUDComponent(GameObject& pOwner, std::string text, int initalValue/*, unsigned int subID*/)
		: BaseComponent(pOwner),
		/*IObserver(subID),*/
		m_Value(initalValue),
		m_Text(text)
	{
		m_Text = m_Text + ": ";
		auto iniText = m_Text + std::to_string(m_Value);
		std::unique_ptr<TextComponent> textComp = std::make_unique<TextComponent>(pOwner, iniText, ResourceManager::GetInstance().GetFont("Minecraft.ttf", 20));
		m_TextComponent = textComp.get();
		GetOwner()->AddComponent(std::move(textComp));
	}

	HUDComponent::~HUDComponent()
	{

	}

	void HUDComponent::Render()
	{

	}

	void HUDComponent::Update()
	{

	}



	void HUDComponent::SetValue(int value)
	{
		m_Value = value;
		std::stringstream stream;
		stream << m_Value;
		std::string newText = m_Text + stream.str();

		m_TextComponent->SetText(newText);
	}

}