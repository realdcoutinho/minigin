#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextObject.h"
#include "RotatorComponent.h"
#include "Scene.h"
#include "FPS.h"

#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	std::shared_ptr go = std::make_shared<dae::GameObject>();
	go.get()->InitializeTransformComponent();
	std::unique_ptr textureComponent = std::make_unique<dae::TextureComponent>(go, "background.tga");
	go.get()->AddComponent(std::move(textureComponent));
	//go->SetTexture("background.tga");
	scene.Add(go);

	go = std::make_shared<dae::GameObject>();
	go.get()->InitializeTransformComponent();
	std::unique_ptr textureComponentLogo = std::make_unique<dae::TextureComponent>(go, "logo.tga");
	go.get()->AddComponent(std::move(textureComponentLogo));
	go->SetPosition(216, 180);
	scene.Add(go);

	std::shared_ptr titleObject = std::make_shared<dae::GameObject>();
	titleObject.get()->InitializeTransformComponent();
	std::unique_ptr txtComp = std::make_unique<dae::TextComponent>(titleObject, "Programming 4 Assignment", font);
	titleObject->AddComponent(std::move(txtComp));
	titleObject->SetPosition(80, 20);

	scene.Add(titleObject);

	std::shared_ptr fpsObject = std::make_shared<dae::GameObject>();
	fpsObject.get()->InitializeTransformComponent();
	fpsObject.get()->SetPosition(216, 100);
	std::unique_ptr fpsComponent = std::make_unique<dae::FPSComponent>(fpsObject, "fpsCounter", font);



	fpsObject->AddComponent(std::move(fpsComponent));


	/*std::shared_ptr Child = std::make_shared<dae::GameObject>();
	Child.get()->InitializeTransformComponent();
	std::unique_ptr fpsComponentChild = std::make_unique<dae::TextComponent>(Child, "Child", font);
	Child->AddComponent(std::move(fpsComponentChild));
	Child.get()->SetPosition(200, 0);
	Child.get()->SetParent(std::move(fpsObject));



	std::shared_ptr grandchild = std::make_shared<dae::GameObject>();
	grandchild.get()->InitializeTransformComponent();
	std::unique_ptr fpsComponentGrandChild = std::make_unique<dae::TextComponent>(grandchild, "Grand", font);
	grandchild->AddComponent(std::move(fpsComponentGrandChild));
	grandchild.get()->SetPosition(0, 100);
	grandchild.get()->SetParent(std::move(Child));*/


	scene.Add(fpsObject);

	std::shared_ptr bertParent = std::make_shared<dae::GameObject>();
	bertParent.get()->InitializeTransformComponent();
	bertParent.get()->SetPosition(250, 350);
	std::unique_ptr bertTexture = std::make_unique<dae::TextureComponent>(bertParent, "bert.png");
	bertParent->AddComponent(std::move(bertTexture));

	float radius = 70;
	float speed = 4;
	std::unique_ptr rotator = std::make_unique<dae::RotatorComponent>(bertParent, radius, speed);
	bertParent->AddComponent(std::move(rotator));


	std::shared_ptr bertChild = std::make_shared<dae::GameObject>();
	bertChild.get()->InitializeTransformComponent();
	std::unique_ptr bertTextureChild = std::make_unique<dae::TextureComponent>(bertChild, "bert.png");
	bertChild->AddComponent(std::move(bertTextureChild));
	radius = 25;
	speed = 15;
	std::unique_ptr rotatorChild = std::make_unique<dae::RotatorComponent>(bertChild, radius, speed);
	bertChild->AddComponent(std::move(rotatorChild));


	bertChild.get()->SetParent(std::move(bertParent));

	scene.Add(bertParent);
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}