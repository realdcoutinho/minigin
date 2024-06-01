#pragma once
#include "BaseComponent.h"
namespace dae
{
	class GameObject;
	class TextureComponent;
	class Scene;
	class HUDLivesComponent final : public BaseComponent
	{
	public:
		HUDLivesComponent(GameObject& pOwner, Scene& scene, int initialLives = 3);
		~HUDLivesComponent();

		void Render() override;
		void Update() override;

		void Hit();

	private:
		int m_Lives;

		TextureComponent* m_LivesOne;
		TextureComponent* m_LivesTwo;
		TextureComponent* m_LivesThree;

		GameObject* m_LivesOneGO;
		GameObject* m_LivesTwoGO;
		GameObject* m_LivesThreeGO;
	};
}


