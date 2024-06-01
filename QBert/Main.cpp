
#include <SDL.h>


#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>

#include <SDL_mixer.h>

#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "TextObject.h"
#include "RotatorComponent.h"
#include "Scene.h"
#include "PlotGraphComponent.h"
#include "Controller.h"
#include "FPSComponent.h"
#include "Input.h"
#include "Command.h"
#include "InputManager.h"
#include "MovementComponent.h"
#include "ScoreComponent.h"
#include "HealthComponent.h"
#include "Subject.h"
#include "HUDComponent.h"
#include "Observer.h"
#include "CharacterComponent.h"
#include "TransformComponent.h"
#include "BaseEvent.h"
#include "EventManager.h"
#include "AudioSystem.h"
#include "ServiceLocator.h"
#include "SoundLibrary.h"
#include "QbertEvents.h"
#include "TriangularGrid.h"
#include "GridNavigator.h"
#include "QBertCharacterComponent.h"
#include "TileInteractor.h"
#include "EnemyCharacterComponent.h"
#include "SamSlickComponent.h"
#include "CoilyComponent.h"
#include "QBertComponent.h"
#include "LevelManager.h"
#include "Listeners.h"
#include "EventDispatcher.h"
#include "InputManager.h"
#include "GridNode.h"

#include "GameLauncher.h"

//
//
//void SceneOne(dae::Scene& scene)
//{
//
//
//
//
//
//
//	_TTF_Font* font = dae::ResourceManager::GetInstance().GetFont("Lingua.otf", 17);
//
//	dae::ResourceManager::GetInstance().GetSound("overworld.wav");
//	auto& soundSystem = dae::ServiceLocator::GetAudioService();
//	//auto& soundSystem = dae::ServiceLocator::GetService(dae::ServiceType::Audio);
//
//	soundSystem->PlaySound(static_cast<unsigned short>(SoundID::LevelSound), 1, 1);
//	//soundSystem->PlaySound(static_cast<unsigned short>(SoundID::LevelSound), 1, 1);
//	//soundSystem->PlaySound(static_cast<unsigned short>(SoundID::LevelSound), 1, 1);
//	//soundSystem->PlaySound(static_cast<unsigned short>(SoundID::LevelSound), 1, 1);
//
//	dae::ResourceManager::GetInstance().GetSound("brickBreak.wav");
//	dae::ResourceManager::GetInstance().GetSound("wow.wav");
//
//
//
//
//
//
//
//
//
//
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
//	std::unique_ptr muteAllSounds = std::make_unique<dae::MuteAllSounds>();
//	input.AddActionCommand(SDL_SCANCODE_M, SDL_KEYDOWN, std::move(muteAllSounds));
//
//	std::unique_ptr reduceSounds = std::make_unique<dae::ReduceSound>();
//	input.AddActionCommand(SDL_SCANCODE_DOWN, SDL_KEYDOWN, std::move(reduceSounds));
//
//	std::unique_ptr increaseSounds = std::make_unique<dae::IncreaseSound>();
//	input.AddActionCommand(SDL_SCANCODE_UP, SDL_KEYDOWN, std::move(increaseSounds));
//
//
//
//	auto pointsCommand = std::make_unique<dae::AddPoints>(*playerOne.get());
//	input.AddActionCommand(SDL_SCANCODE_L, SDL_KEYDOWN, std::move(pointsCommand));
//
//	auto healthPickUpCommand = std::make_unique<dae::HealthPickUp>(*playerOne.get());
//	input.AddActionCommand(SDL_SCANCODE_H, SDL_KEYDOWN, std::move(healthPickUpCommand));
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
//	auto hudLivesComponent = std::make_unique<dae::HUDComponent>(*HUDLives.get(), "Lives", 3, playerOne.get()->GetID());
//	//playerOne->GetComponent<dae::HealthComponent>()->AddObserver(hudLivesComponent.get(), dae::Event::HealthChange);
//	//playerOne->GetComponent<dae::HealthComponent>()->AddObserver(hudLivesComponent.get(), dae::Event::PlayerDeath);
//
//	//dae::MyEvent healthChange{};
//	//healthChange.type = dae::EventType::HealthChange;
//	//healthChange.entityId = playerOne.get()->GetID();
//	//healthChange.sender = playerOne.get();
//
//	//int playerHealth = 100;  // Example health value
//
//	//auto& healthRef = playerOne.get()->GetComponent<dae::HealthComponent>()->GetHealthRef();
//	//auto healthComp = playerOne.get()->GetComponent<dae::HealthComponent>();
//
//	//dae::HealthChangeEvent healthChangeEvent
//	//(
//	//	playerOne.get()->GetID(),  // entityId
//	//	playerOne.get(),           // sender
//	//	dae::EventType::HealthChange, // type of the event
//	//	healthRef,     // reference to health
//	//	[&](int newHealth) { healthComp.SetHealth(newHealth); }
//	//);
//
//	//dae::HealthChangeEvent healthChangeEvent(
//	//	playerOne.get()->GetID(),
//	//	playerOne.get(),
//	//	dae::EventType::HealthChange,
//	//	healthRef,
//	//	[&](int newHealth) { healthComp->SetHealth(newHealth); }
//	//);
//
//
//
//	dae::EventManager::GetInstance().AddObserver(hudLivesComponent.get(), static_cast<unsigned int>(dae::EventType::HealthChange));
//
//
//	//playerOne->GetComponent<dae::HealthComponent>()->AddObserver(hudLivesComponent.get(), 
//	//	dae::EventType::HealthChange);
//
//	HUDLives->AddComponent(std::move(hudLivesComponent));
//	HUDLives->SetParent(HUD.get());
//
//
//
//	auto HUDScore = std::make_unique<dae::GameObject>();
//	HUDScore->InitializeTransformComponent();
//	HUDScore->SetLocalPosition(0, 25);
//	auto hudScoreComponent = std::make_unique<dae::HUDComponent>(*HUDScore.get(), "Score", 0, playerOne.get()->GetID());
//
//	dae::EventManager::GetInstance().AddObserver(hudScoreComponent.get(), static_cast<unsigned int>(dae::EventType::ScoreChange));
//
//	//dae::MyEvent scoreChange{};
//	//scoreChange.type = dae::EventType::ScoreChange;
//	//scoreChange.entityId = playerOne.get()->GetID();
//	//scoreChange.sender = playerOne.get();
//	//dae::EventManager::GetInstance().AddObserver(hudScoreComponent.get(), scoreChange);
//
//	//playerOne->GetComponent<dae::ScoreComponent>()->AddObserver(hudScoreComponent.get(), dae::Event::ScoreChange);
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
//	muteAllSounds = std::make_unique<dae::MuteAllSounds>();
//	input.AddActionCommand(controller1, dae::Controller::ControllerButton::Y, std::move(muteAllSounds));
//
//	HUD = std::make_unique<dae::GameObject>();
//	HUD->InitializeTransformComponent();
//	HUD->SetLocalPosition(10, 120);
//
//	HUDLives = std::make_unique<dae::GameObject>();
//	HUDLives->InitializeTransformComponent();
//	HUDLives->SetLocalPosition(0, 0);
//	hudLivesComponent = std::make_unique<dae::HUDComponent>(*HUDLives.get(), "Lives", 3, playerTwo.get()->GetID());
//
//	//healthChange.type = dae::EventType::HealthChange;
//	//healthChange.entityId = playerTwo.get()->GetID();
//	//healthChange.sender = playerTwo.get();
//	//dae::EventManager::GetInstance().AddObserver(hudLivesComponent.get(), healthChange);
//
//	//dae::EventManager::GetInstance().AddObserver(hudLivesComponent.get(), playerTwo.get()->GetID());
//
//	//playerTwo->GetComponent<dae::HealthComponent>()->AddObserver(hudLivesComponent.get(), dae::Event::HealthChange);
//	//playerTwo->GetComponent<dae::HealthComponent>()->AddObserver(hudLivesComponent.get(), dae::Event::PlayerDeath);
//	HUDLives->AddComponent(std::move(hudLivesComponent));
//	HUDLives->SetParent(HUD.get());
//
//
//	HUDScore = std::make_unique<dae::GameObject>();
//	HUDScore->InitializeTransformComponent();
//	HUDScore->SetLocalPosition(0, 25);
//	hudScoreComponent = std::make_unique<dae::HUDComponent>(*HUDScore.get(), "Score", 0, playerTwo.get()->GetID());
//	//dae::EventManager::GetInstance().AddObserver(hudScoreComponent.get(), playerTwo.get()->GetID());
//
//	//playerTwo->GetComponent<dae::ScoreComponent>()->AddObserver(hudScoreComponent.get(), dae::Event::ScoreChange);
//
//
//	//scoreChange.type = dae::EventType::ScoreChange;
//	//scoreChange.entityId = playerTwo.get()->GetID();
//	//scoreChange.sender = playerTwo.get();
//	//dae::EventManager::GetInstance().AddObserver(hudScoreComponent.get(), scoreChange);
//
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
//
//	intructions = std::make_unique<dae::GameObject>();
//	intructions->InitializeTransformComponent();
//	intructions->SetLocalPosition(10, 250);
//	intructionsText = std::make_unique<dae::TextComponent>(*intructions.get(), "M = (un)Mute ALL sounds, Down Key = -Volume , Up Key = +Volume", font);
//	intructions->AddComponent(std::move(intructionsText));
//	scene.Add(std::move(intructions));
//
//
//	intructions = std::make_unique<dae::GameObject>();
//	intructions->InitializeTransformComponent();
//	intructions->SetLocalPosition(10, 280);
//	intructionsText = std::make_unique<dae::TextComponent>(*intructions.get(), "Controller -> Y = (un)Mute All Sounds", font);
//	intructions->AddComponent(std::move(intructionsText));
//	scene.Add(std::move(intructions));
//
//
//	intructions = std::make_unique<dae::GameObject>();
//	intructions->InitializeTransformComponent();
//	intructions->SetLocalPosition(10, 300);
//	intructionsText = std::make_unique<dae::TextComponent>(*intructions.get(), "Damage and health also play sounds", font);
//	intructions->AddComponent(std::move(intructionsText));
//	scene.Add(std::move(intructions));
//
//
//	//playerOne->GetComponent<dae::HealthComponent>()->AddObserver(scene.m_pPlayerDeathObserver.get(), dae::Event::PlayerDeath);
//
//
//	scene.Add(std::move(playerOne));
//	scene.Add(std::move(playerTwo));
//
//	//std::unique_ptr grid = std::make_unique<dae::TriangularGrid>(32, 32, 20, 15);
//
//
//
//
//}

void LevelOne(dae::Scene& scene)
{
	scene;


	//std::unique_ptr gridObject = std::make_unique<dae::GameObject>();
	//gridObject->InitializeTransformComponent();
	//gridObject->SetLocalPosition(0, 0);

	//auto& input = scene.GetSceneInput();


	//auto gridComponent = std::make_unique<dae::TriangularGrid>(*gridObject.get(), 2, 0);


	//std::unique_ptr<dae::NodeListener> nodeListener = std::make_unique<dae::NodeListener>(gridObject->GetID());
	//dae::EventDispatcher::GetInstance().SubscribeListener(std::move(nodeListener));

	//auto changeTile = std::make_unique<dae::UpgradeTileCommand>(gridComponent.get());
	//input.AddActionCommand(SDL_SCANCODE_1, SDL_KEYDOWN, std::move(changeTile));




	//std::unique_ptr bert = std::make_unique<dae::GameObject>();
	//bert->InitializeTransformComponent();
	//auto playerComponent = std::make_unique<dae::QBertComponent>(*bert.get(), *gridComponent.get());

	//auto HUD = std::make_unique<dae::GameObject>();
	//HUD->InitializeTransformComponent();
	//HUD->SetLocalPosition(10, 70);

	//auto HUDScore = std::make_unique<dae::GameObject>();
	//HUDScore->InitializeTransformComponent();
	//HUDScore->SetLocalPosition(0, 25);
	//auto id = bert.get()->GetID();
	//id;
	//auto hudScoreComponent = std::make_unique<dae::HUDComponent>(*HUDScore.get(), "Score", 0/*, id*/);
	////dae::EventManager::GetInstance().AddObserver(hudScoreComponent.get(), static_cast<unsigned int>(dae::EventType::ScoreChange));
	//
	//
	//
	//
	//std::unique_ptr<dae::ScoreListener> scoreListenerHUD = std::make_unique<dae::ScoreListener>(*HUDScore.get(), bert->GetID());
	//std::unique_ptr<dae::ScoreListener> scoreListenerPlayer = std::make_unique<dae::ScoreListener>(*bert.get(), bert->GetID());
	//dae::EventDispatcher::GetInstance().SubscribeListener(std::move(scoreListenerHUD));
	//dae::EventDispatcher::GetInstance().SubscribeListener(std::move(scoreListenerPlayer));

	//
	//HUDScore->AddComponent(std::move(hudScoreComponent));



	////auto& node = gridComponent->GetNode(0);
	////std::unique_ptr<dae::GridNavigator> gridNavigator = std::make_unique<dae::GridNavigator>(*bert.get(), *gridComponent.get(), node);

	//bert->SetLocalPosition(gridComponent->GetNode(4).GetNodeInfo().centerPos);
	//






	//auto movementCommandBert = std::make_unique<dae::GridMovement>(*bert.get(), *gridComponent.get());
	//unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();
	//input.AddAxisCommand(controller1, std::move(movementCommandBert));





	//bert->AddComponent(std::move(playerComponent));
	//auto& levelManager = dae::LevelManager::GetInstance();
	//levelManager.SetGrid(gridComponent.get());


	//auto slick = std::make_unique<dae::GameObject>();
	//slick->InitializeTransformComponent();
	//auto slickComponent = std::make_unique<dae::SamSlickComponent>(*slick.get(), *gridComponent.get());
	//slick->SetLocalPosition(gridComponent->GetStartingPosition());
	//slick->AddComponent(std::move(slickComponent));
	//scene.Add(std::move(slick));

	//auto coily = std::make_unique<dae::GameObject>();
	//coily->InitializeTransformComponent();
	//auto coilyComponent = std::make_unique<dae::CoilyComponent>(*coily.get(), *gridComponent.get());
	//coily->SetLocalPosition(gridComponent->GetStartingPosition());
	//levelManager.SetCoily(coilyComponent.get());
	//coily->AddComponent(std::move(coilyComponent));
	//scene.Add(std::move(coily));




	//gridObject->AddComponent(std::move(gridComponent));

	//_TTF_Font* font = dae::ResourceManager::GetInstance().GetFont("Lingua.otf", 17);

	//auto intructions = std::make_unique<dae::GameObject>();
	//intructions->InitializeTransformComponent();
	//intructions->SetLocalPosition(10, 50);
	//auto intructionsText = std::make_unique<dae::TextComponent>(*intructions.get(), "USE DPAD. State on Player Facing", font);
	//intructions->AddComponent(std::move(intructionsText));
	//
	//


	//
	//
	//scene.Add(std::move(intructions));


	//scene.Add(std::move(gridObject));
	//scene.Add(std::move(bert));
	////scene.Add(std::move(goTileObserver));
	//scene.Add(std::move(HUD));
	//scene.Add(std::move(HUDScore));

	////auto& soundSystem = dae::ServiceLocator::GetAudioService();
	////soundSystem->PlaySound(static_cast<unsigned short>(SoundID::LevelSound), 1, 1);


}

void load()
{
	////auto& demo = dae::SceneManager::GetInstance().CreateScene("Demo");
	////SceneOne(demo);
	//auto& level = dae::SceneManager::GetInstance().CreateScene("LevelOne");
	//LevelOne(level);


	////auto& level2 = dae::SceneManager::GetInstance().CreateScene("LevelTwo");
	////level2;

	////dae::SceneManager::GetInstance().SetActiveScene(level);
	//
	////dae::SceneManager::GetInstance().SetActiveScene(level2);

}

int main(int, char*[]) 
{

	
	dae::Minigin engine("../Data/");

	std::unique_ptr<dae::GameLauncher> launcher = std::make_unique<dae::GameLauncher>();



	engine.Run(load);
    
	
	
	return 0;
}