#include "HUDLivesComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "Scene.h"
#include <memory>

namespace dae
{
	HUDLivesComponent::HUDLivesComponent(GameObject& pOwner, Scene& scene, int initialLives)
				: BaseComponent(pOwner),
		m_Lives(initialLives)
	{
		glm::vec2 scale{ 2.f, 2.f };

		std::unique_ptr<GameObject> livesOne = std::make_unique<GameObject>();
		livesOne->InitializeTransformComponent();
		livesOne->SetLocalPosition({ 0.0f, 00.0f });
		std::unique_ptr<TextureComponent> livesOneTexture = std::make_unique<TextureComponent>(*livesOne, "Heart.png");
		livesOneTexture->SetScale(scale);
		livesOne->AddComponent(std::move(livesOneTexture));
		livesOne->SetParent(&pOwner);

		std::unique_ptr<GameObject> livesTwo = std::make_unique<GameObject>();
		livesTwo->InitializeTransformComponent();
		livesTwo->SetLocalPosition({0.0f, 40.0f});
		std::unique_ptr<TextureComponent> livesTwoTexture = std::make_unique<TextureComponent>(*livesTwo, "Heart.png");
		livesTwoTexture->SetScale(scale);
		livesTwo->AddComponent(std::move(livesTwoTexture));
		livesTwo->SetParent(&pOwner);

		std::unique_ptr<GameObject> livesThree = std::make_unique<GameObject>();
		livesThree->InitializeTransformComponent();
		livesThree->SetLocalPosition({ 0.0f, 80.0f });
		std::unique_ptr<TextureComponent> livesThreeTexture = std::make_unique<TextureComponent>(*livesThree, "Heart.png");
		livesThreeTexture->SetScale(scale);
		livesThree->AddComponent(std::move(livesThreeTexture));
		livesThree->SetParent(&pOwner);




		m_LivesOneGO = livesOne.get();
		m_LivesTwoGO = livesTwo.get();
		m_LivesThreeGO = livesThree.get();

		scene.Add(std::move(livesOne));
		scene.Add(std::move(livesTwo));
		scene.Add(std::move(livesThree));
	}

	HUDLivesComponent::~HUDLivesComponent()
	{

	}

	void HUDLivesComponent::Render()
	{

	}

	void HUDLivesComponent::Update()
	{

	}

	void HUDLivesComponent::Set(int value)
	{
		m_Lives = value;
		if (m_Lives == 2)
		{
			m_LivesThreeGO->SetActive(false);
		}
		else if (m_Lives == 1)
		{
			m_LivesThreeGO->SetActive(false);
			m_LivesTwoGO->SetActive(false);
		}
		else if (m_Lives == 0)
		{
			m_LivesThreeGO->SetActive(false);
			m_LivesTwoGO->SetActive(false);
			m_LivesOneGO->SetActive(false);
		}
	}


}
