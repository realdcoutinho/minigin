//#pragma once
//#include "BaseComponent.h"
//#include "Observer.h"
//#include "Event.h"
//
//namespace dae
//{
//	class TextComponent;
//
//	class HUDComponent : public BaseComponent, public IObserver
//	{
//	public:
//		HUDComponent(GameObject& pOwner, std::string text, int initalValue, unsigned int subID);
//		~HUDComponent();
//
//		void Render() override;
//		void Update() override;
//
//		void SetValue(int value);
//
//		virtual void OnNotify(BaseEvent* event);
//		virtual void OnEvent(dae::Event event);
//
//
//
//	private:
//		
//		TextComponent* m_TextComponent;
//		std::string m_Text;
//		int m_Value{ 0 };
//	};
//}
//
//
