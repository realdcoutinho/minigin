//#include "HUDComponent.h"
//#include "TextComponent.h"
//#include "ResourceManager.h"
//#include "GameObject.h"
//#include <sstream> // Include stringstream
//#include "CharacterComponent.h"
//#include <memory>
//
//
//namespace dae 
//{
//	HUDComponent::HUDComponent(GameObject& pOwner, std::string text, int initalValue, unsigned int subID)
//		: BaseComponent(pOwner),
//		IObserver(subID),
//		m_Value(initalValue),
//		m_Text(text)
//	{
//		m_Text = m_Text + ": ";
//		auto iniText = m_Text + std::to_string(m_Value);
//		std::unique_ptr<TextComponent> textComp = std::make_unique<TextComponent>(pOwner, iniText, ResourceManager::GetInstance().GetFont("Lingua.otf", 20));
//		m_TextComponent = textComp.get();
//		GetOwner()->AddComponent(std::move(textComp));
//	}
//
//	HUDComponent::~HUDComponent()
//	{
//
//	}
//
//	void HUDComponent::Render()
//	{
//
//	}
//
//	void HUDComponent::Update()
//	{
//
//	}
//
//	void HUDComponent::OnNotify(BaseEvent* event)
//	{
//		auto eventType = static_cast<EventType>(event->type);
//
//		switch (eventType)
//		{
//			case EventType::HealthChange:
//			case EventType::ScoreChange:
//			{
//				// Attempt to cast the base event to a health event
//				auto statEvent = dynamic_cast<TemplateEvent<int>*>(event);
//				if (statEvent)
//				{
//					// Successfully cast to HealthEvent, now you can use health-specific data
//					int newVal = statEvent->GetValue();
//					// Do something with the new health value, e.g., update a health bar
//					SetValue(newVal);
//				}
//				break;
//			}
//			case EventType::PlayerDeath:
//			{
//				m_TextComponent->SetText("Player Dead");
//				break;
//			}
//		}
//	}
//
//	void HUDComponent::OnEvent(dae::Event event)
//	{
//		event;
//		//simply for no warning reasons as of this very moment
//	}
//
//	void HUDComponent::SetValue(int value)
//	{
//		std::stringstream stream;
//		stream << value;
//		std::string newText = m_Text + stream.str();
//
//		m_TextComponent->SetText(newText);
//	}
//
//}