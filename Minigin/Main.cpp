//#include <SDL.h>
//
//#if _DEBUG
//// ReSharper disable once CppUnusedIncludeDirective
//#if __has_include(<vld.h>)
//#include <vld.h>
//#endif
//#endif
//
//#include "Minigin.h"
//#include "SceneManager.h"
//#include "ResourceManager.h"
//#include "TextureComponent.h"
//#include "TextObject.h"
//#include "RotatorComponent.h"
//#include "Scene.h"
//#include "PlotGraphComponent.h"
//#include "Controller.h"
//#include "FPSComponent.h"
//#include "Input.h"
//#include "Command.h"
//#include "InputManager.h"
//#include "MovementComponent.h"
//#include "ScoreComponent.h"
//#include "HealthComponent.h"
//#include "Subject.h"
//#include "HUDComponent.h"
//#include "Observer.h"
//#include "CharacterComponent.h"
//#include "TransformComponent.h"
//#include "Event.h"
//
//
//void load()
//{
//	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
//	dae::SceneManager::GetInstance().SetActiveScene(scene);
//	_TTF_Font* font = dae::ResourceManager::GetInstance().GetFont("Lingua.otf", 17);
//
//	//std::unique_ptr go = std::make_unique<dae::GameObject>();
//	//go->InitializeTransformComponent();
//	//std::unique_ptr textureComponent = std::make_unique<dae::TextureComponent>(*go.get(), "background.tga");
//	//go->AddComponent(std::move(textureComponent));
//	//scene.Add(std::move(go));
//
//	//go = std::make_unique<dae::GameObject>();
//	//go->InitializeTransformComponent();
//	//std::unique_ptr textureComponentLogo = std::make_unique<dae::TextureComponent>(*go.get(), "logo.tga");
//	//go->AddComponent(std::move(textureComponentLogo));
//	//go->SetLocalPosition(216, 180);
//	//scene.Add(std::move(go));
//
//	//std::unique_ptr titleObject = std::make_unique<dae::GameObject>();
//	//titleObject->InitializeTransformComponent();
//	//std::unique_ptr txtComp = std::make_unique<dae::TextComponent>(*titleObject.get(), "Programming 4 Assignment", font);
//	//titleObject->AddComponent(std::move(txtComp));
//	//titleObject->SetLocalPosition(80, 20);
//
//	//scene.Add(std::move(titleObject));
//
//	//std::unique_ptr fpsObject = std::make_unique<dae::GameObject>();
//	//fpsObject->InitializeTransformComponent();
//	//fpsObject->SetLocalPosition(216, 100);
//	//std::unique_ptr fpsComponent = std::make_unique<dae::FPSComponent>(*fpsObject.get());
//
//	//fpsObject->AddComponent(std::move(fpsComponent));
//	//scene.Add(std::move(fpsObject));
//
//
//	
//	auto& input = scene.GetSceneInput();
//
//
//	float speed = 90.0f;
//	std::unique_ptr playerOne = std::make_unique<dae::GameObject>();
//	playerOne->InitializeTransformComponent();
//	playerOne->SetLocalPosition(250, 350);
//	auto playerComponent = std::make_unique<dae::CharacterComponent>(*playerOne.get(), "bert.png", "bert");
//
//
//
//	playerOne->AddComponent(std::move(playerComponent));
//	std::unique_ptr bertMovement = std::make_unique<dae::MovementComponent>(*playerOne.get(), speed);
//	playerOne->AddComponent(std::move(bertMovement));
//	auto damageCommand = std::make_unique<dae::Damage>(*playerOne.get());
//	input.AddActionCommand(SDL_SCANCODE_K, SDL_KEYDOWN, std::move(damageCommand));
//
//	auto pointsCommand = std::make_unique<dae::AddPoints>(*playerOne.get());
//	input.AddActionCommand(SDL_SCANCODE_L, SDL_KEYDOWN, std::move(pointsCommand));
//
//	auto healthPickUpCommand = std::make_unique<dae::HealthPickUp>(*playerOne.get());
//	input.AddActionCommand(SDL_SCANCODE_H , SDL_KEYDOWN, std::move(healthPickUpCommand));
//
//
//	auto movementCommandBert = std::make_unique<dae::MovementCommandAxis>(*playerOne.get());
//	input.AddAxisCommand(std::move(movementCommandBert));
//
//	auto HUD = std::make_unique<dae::GameObject>();
//	HUD->InitializeTransformComponent();
//	HUD->SetLocalPosition(10, 70);
//
//	auto HUDLives = std::make_unique<dae::GameObject>();
//	HUDLives->InitializeTransformComponent();
//	HUDLives->SetLocalPosition(0, 0);
//	auto hudLivesComponent = std::make_unique<dae::HUDComponent>(*HUDLives.get(), "Lives", 3);
//	playerOne->GetComponent<dae::HealthComponent>()->AddObserver(hudLivesComponent.get(), dae::Event::HealthChange);
//	playerOne->GetComponent<dae::HealthComponent>()->AddObserver(hudLivesComponent.get(), dae::Event::PlayerDeath);
//	HUDLives->AddComponent(std::move(hudLivesComponent));
//	HUDLives->SetParent(HUD.get());
//
//
//
//	auto HUDScore = std::make_unique<dae::GameObject>();
//	HUDScore->InitializeTransformComponent();
//	HUDScore->SetLocalPosition(0, 25);
//	auto hudScoreComponent = std::make_unique<dae::HUDComponent>(*HUDScore.get(), "Score", 0);
//	playerOne->GetComponent<dae::ScoreComponent>()->AddObserver(hudScoreComponent.get(), dae::Event::ScoreChange);
//	HUDScore->AddComponent(std::move(hudScoreComponent));
//	HUDScore->SetParent(HUD.get());
//
//	scene.Add(std::move(HUD));
//	scene.Add(std::move(HUDLives));
//	scene.Add(std::move(HUDScore));
//
//
//	std::unique_ptr playerTwo = std::make_unique<dae::GameObject>();
//	playerTwo->InitializeTransformComponent();
//	playerTwo->SetLocalPosition(200, 400);
//	playerComponent = std::make_unique<dae::CharacterComponent>(*playerTwo.get(), "bert.png", "playerTwo");
//	playerTwo->AddComponent(std::move(playerComponent));
//	std::unique_ptr playerTwoMovement = std::make_unique<dae::MovementComponent>(*playerTwo.get(), speed * 2.0f);
//	playerTwo->AddComponent(std::move(playerTwoMovement));
//
//	auto movementCommand = std::make_unique<dae::MovementCommandAxis>(*playerTwo.get());
//
//	unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();
//	input.AddAxisCommand(controller1, std::move(movementCommand));
//
//
//	damageCommand = std::make_unique<dae::Damage>(*playerTwo.get());
//	input.AddActionCommand(controller1, dae::Controller::ControllerButton::A, std::move(damageCommand));
//
//	pointsCommand = std::make_unique<dae::AddPoints>(*playerTwo.get());
//	input.AddActionCommand(controller1, dae::Controller::ControllerButton::X, std::move(pointsCommand));
//
//	healthPickUpCommand = std::make_unique<dae::HealthPickUp>(*playerTwo.get());
//	input.AddActionCommand(controller1, dae::Controller::ControllerButton::B, std::move(healthPickUpCommand));
//
//
//
//	HUD = std::make_unique<dae::GameObject>();
//	HUD->InitializeTransformComponent();
//	HUD->SetLocalPosition(10, 120);
//
//	HUDLives = std::make_unique<dae::GameObject>();
//	HUDLives->InitializeTransformComponent();
//	HUDLives->SetLocalPosition(0, 0);
//	hudLivesComponent = std::make_unique<dae::HUDComponent>(*HUDLives.get(), "Lives", 3);
//	playerTwo->GetComponent<dae::HealthComponent>()->AddObserver(hudLivesComponent.get(), dae::Event::HealthChange);
//	playerTwo->GetComponent<dae::HealthComponent>()->AddObserver(hudLivesComponent.get(), dae::Event::PlayerDeath);
//	HUDLives->AddComponent(std::move(hudLivesComponent));
//	HUDLives->SetParent(HUD.get());
//
//
//	HUDScore = std::make_unique<dae::GameObject>();
//	HUDScore->InitializeTransformComponent();
//	HUDScore->SetLocalPosition(0, 25);
//	hudScoreComponent = std::make_unique<dae::HUDComponent>(*HUDScore.get(), "Score", 0);
//	playerTwo->GetComponent<dae::ScoreComponent>()->AddObserver(hudScoreComponent.get(), dae::Event::ScoreChange);
//	HUDScore->AddComponent(std::move(hudScoreComponent));
//	HUDScore->SetParent(HUD.get());
//
//	scene.Add(std::move(HUD));
//	scene.Add(std::move(HUDLives));
//	scene.Add(std::move(HUDScore));
//
//	auto intructions = std::make_unique<dae::GameObject>();
//	intructions->InitializeTransformComponent();
//	intructions->SetLocalPosition(10, 10);
//	auto intructionsText = std::make_unique<dae::TextComponent>(*intructions.get(), "Player 1: K = Damage, L = Points, H = ++Health, Use WASD to move", font);
//	intructions->AddComponent(std::move(intructionsText));
//	scene.Add(std::move(intructions));
//
//
//	intructions = std::make_unique<dae::GameObject>();
//	intructions->InitializeTransformComponent();
//	intructions->SetLocalPosition(10, 40);
//	intructionsText = std::make_unique<dae::TextComponent>(*intructions.get(), "Player 2: A = Damage, X = Points, B = ++Health, Use DPAD to move", font);
//	intructions->AddComponent(std::move(intructionsText));
//	scene.Add(std::move(intructions));
//
//
//	playerOne->GetComponent<dae::HealthComponent>()->AddObserver(scene.m_pPlayerDeathObserver.get(), dae::Event::PlayerDeath);
//
//
//	scene.Add(std::move(playerOne));
//	scene.Add(std::move(playerTwo));
//}
//
//int main(int, char*[]) 
//{
//	dae::Minigin engine("../Data/");
//	engine.Run(load);
//    return 0;
//}