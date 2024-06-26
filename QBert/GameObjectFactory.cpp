#include "GameObjectFactory.h"
#include "GameObject.h"
#include "CoilyComponent.h"
#include "TriangularGrid.h"
#include "SamSlickComponent.h"
#include "QBertComponent.h"
#include "GridNode.h"
#include "LevelManager.h"
#include "GameInfo.h"
#include "TextComponent.h"
#include "Scene.h"
#include "HUDComponent.h"
#include "HUDLivesComponent.h"
#include "FPSComponent.h"
#include "Listeners.h"
#include "InputManager.h"
#include "Input.h"
#include "EventDispatcher.h"
#include "GridNode.h"
#include "UggWrongwayComponent.h"
#include "SelectModeComponent.h"
#include "Input.h"
#include "Command.h"
#include "GameOverComponent.h"
#include "HighScoreComponent.h"
#include "GameInfoLoader.h"


namespace dae
{
	GameObject& GameObjectFactory::InitializePlayerOne(Scene& scene, TriangularGrid& pGrid, GameInfo& gi)
	{
		int startingNode = 4;
		int gameMode = gi.gameMode;
		if (gameMode == 2)
			startingNode = 37;

		int playerNumber = 1;

		auto& bert = GameObjectFactory::GetInstance().CreateQbert(scene, pGrid, startingNode, playerNumber);
		glm::vec2 scoreHUDPos{ 10, 70 };
		auto& HUDScore = GameObjectFactory::GetInstance().CreateHUDScore(scene, scoreHUDPos);
		glm::vec2 livesHUDPos{ 10, 200 };
		auto& livesHud = GameObjectFactory::GetInstance().CreateHUDLives(scene, livesHUDPos);
		std::shared_ptr<dae::ScoreListener> scoreListenerHUD = std::make_shared<dae::ScoreListener>(HUDScore, bert.GetID());
		std::shared_ptr<dae::ScoreListener> scoreListenerPlayer = std::make_shared<dae::ScoreListener>(bert, bert.GetID());
		dae::EventDispatcher::GetInstance().SubscribeListener(std::move(scoreListenerHUD));
		dae::EventDispatcher::GetInstance().SubscribeListener(std::move(scoreListenerPlayer));

		std::shared_ptr<dae::HealthListener> healthListenerHUD = std::make_shared<dae::HealthListener>(livesHud, bert.GetID());
		std::shared_ptr<dae::HealthListener> healthListenerPlayer = std::make_shared<dae::HealthListener>(bert, bert.GetID());
		dae::EventDispatcher::GetInstance().SubscribeListener(std::move(healthListenerHUD));
		dae::EventDispatcher::GetInstance().SubscribeListener(std::move(healthListenerPlayer));




		auto& input = scene.GetSceneInput();
		auto movementCommandBert = std::make_unique<GridMovement>(bert);
		input.AddAxisCommand(std::move(movementCommandBert));

		auto pauseCommand = std::make_unique<PauseGame>(bert);
		input.AddActionCommand(SDL_SCANCODE_P, SDL_KEYDOWN, std::move(pauseCommand));

		auto muteCommand = std::make_unique<MuteAllSounds>();
		input.AddActionCommand(SDL_SCANCODE_M, SDL_KEYDOWN, std::move(muteCommand));


		CreatePlayerTitle(scene, playerNumber);

		return bert;
	}

	GameObject& GameObjectFactory::InitializePlayerTwo(Scene& scene, TriangularGrid& pGrid, GameInfo& gi)
	{
		int gameMode = gi.gameMode;

		if (gameMode == 3)
		{
			auto& coily = GameObjectFactory::GetInstance().CreateCoily(scene, pGrid, true);


			auto& input = scene.GetSceneInput();
			auto movementCommandBert = std::make_unique<dae::GridMovement>(coily);
			unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();
			input.AddAxisCommand(controller1, std::move(movementCommandBert));

			return coily;
		}

		int staringNode = 43;
		int playerNumber = 2;


		CreatePlayerTitle(scene, playerNumber);

		auto& bert = GameObjectFactory::GetInstance().CreateQbert(scene, pGrid, staringNode, playerNumber);
		glm::vec2 scoreHUDPos{ 550, 70 };
		auto& HUDScore = GameObjectFactory::GetInstance().CreateHUDScore(scene, scoreHUDPos);
		glm::vec2 livesHUDPos{ 600, 200 };
		auto& livesHud = GameObjectFactory::GetInstance().CreateHUDLives(scene, livesHUDPos);
		std::shared_ptr<dae::ScoreListener> scoreListenerHUD = std::make_shared<dae::ScoreListener>(HUDScore, bert.GetID());
		std::shared_ptr<dae::ScoreListener> scoreListenerPlayer = std::make_shared<dae::ScoreListener>(bert, bert.GetID());
		dae::EventDispatcher::GetInstance().SubscribeListener(std::move(scoreListenerHUD));
		dae::EventDispatcher::GetInstance().SubscribeListener(std::move(scoreListenerPlayer));

		std::shared_ptr<dae::HealthListener> healthListenerHUD = std::make_shared<dae::HealthListener>(livesHud, bert.GetID());
		std::shared_ptr<dae::HealthListener> healthListenerPlayer = std::make_shared<dae::HealthListener>(bert, bert.GetID());
		dae::EventDispatcher::GetInstance().SubscribeListener(std::move(healthListenerHUD));
		dae::EventDispatcher::GetInstance().SubscribeListener(std::move(healthListenerPlayer));


		auto& input = scene.GetSceneInput();
		auto movementCommandBert = std::make_unique<dae::GridMovement>(bert);
		unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();
		input.AddAxisCommand(controller1, std::move(movementCommandBert));
		return bert;
	}

	GameObject& dae::GameObjectFactory::CreateCoily(Scene& scene, TriangularGrid& pGrid, bool isPlayable)
	{
		auto coily = std::make_unique<dae::GameObject>();
		coily->InitializeTransformComponent();
		auto coilyComponent = std::make_unique<dae::CoilyComponent>(*coily.get(), pGrid, isPlayable);
		coily->AddComponent(std::move(coilyComponent));

		auto& temp = *coily.get();
		scene.Add(std::move(coily));
		return temp;
	}

	GameObject& GameObjectFactory::CreateSlickSam(Scene& scene, TriangularGrid& pGrid)
	{
		auto slick = std::make_unique<dae::GameObject>();
		slick->InitializeTransformComponent();
		auto slickComponent = std::make_unique<dae::SamSlickComponent>(*slick.get(), pGrid);
		slick->AddComponent(std::move(slickComponent));

		auto& temp = *slick.get();
		scene.Add(std::move(slick));
		return temp;
	}

	GameObject& GameObjectFactory::CreateUggWrongway(Scene& scene, TriangularGrid& pGrid)
	{
		auto uggWrongway = std::make_unique<dae::GameObject>();
		uggWrongway->InitializeTransformComponent();
		auto uggWrongwayComponent = std::make_unique<dae::UggWrongwayComponent>(*uggWrongway.get(), pGrid);
		uggWrongway->AddComponent(std::move(uggWrongwayComponent));

		auto& temp = *uggWrongway.get();
		scene.Add(std::move(uggWrongway));
		return temp;
	}

	GameObject& GameObjectFactory::CreateQbert(Scene& scene, TriangularGrid& pGrid, int startingNode, int player)
	{
		std::unique_ptr bert = std::make_unique<dae::GameObject>();
		bert->InitializeTransformComponent();
		auto playerComponent = std::make_unique<dae::QBertComponent>(*bert.get(), pGrid, startingNode, player);
		bert->SetLocalPosition(pGrid.GetNode(startingNode)->GetNodeInfo().centerPos);
		bert->AddComponent(std::move(playerComponent));

		auto& temp = *bert.get();
		scene.Add(std::move(bert));
		return temp;
	}



	GameObject& GameObjectFactory::CreateGrid(Scene& scene, GameInfo& gi)
	{
		std::unique_ptr gridObject = std::make_unique<dae::GameObject>();
		gridObject->InitializeTransformComponent();
		gridObject->SetLocalPosition(0, 0);
		auto gridComponent = std::make_unique<dae::TriangularGrid>(*gridObject.get(), scene, gi);


		GameObjectFactory::GetInstance().CreateTargetColorNode(scene, gi);
		std::shared_ptr<dae::NodeListener> nodeListener = std::make_shared<dae::NodeListener>(*gridComponent.get(), gridObject->GetID());
		dae::EventDispatcher::GetInstance().SubscribeListener(std::move(nodeListener));
		gridObject->AddComponent(std::move(gridComponent));

		auto& temp = *gridObject.get();
		scene.Add(std::move(gridObject));
		return temp;
	}

	GameObject& GameObjectFactory::CreateTargetColorNode(Scene& scene, GameInfo& gi)
	{
		std::unique_ptr colorNode = std::make_unique<dae::GameObject>();
		colorNode->InitializeTransformComponent();
		colorNode->SetLocalPosition(15, 120);

		auto font = ResourceManager::GetInstance().GetFont("Minecraft.ttf", 23);
		std::unique_ptr textToChange = std::make_unique<TextComponent>(*colorNode.get(), "CHANGE TO", font);
		colorNode->AddComponent(std::move(textToChange));

		std::unique_ptr colorNodeTextureObject = std::make_unique<dae::GameObject>();
		colorNodeTextureObject->InitializeTransformComponent();
		colorNodeTextureObject->SetLocalPosition(150, -5);


		auto idxColor = gi.startColor;
		auto level = gi.level;
		int posY = 1;
		if (level != 2)
		{
			posY = 0;
		}

		glm::vec2 pos = glm::vec2(0, 0);
		glm::vec2 size = glm::vec2(32, 32);

		std::unique_ptr<TextureComponent> colorNodeTexture = std::make_unique<TextureComponent>(*colorNodeTextureObject.get(), "Color Icons Spritesheet.png", 2);
		colorNodeTexture->SetTextureSegments({ 6,2 });
		colorNodeTexture->SetTexturePositionIndex({ idxColor, posY });
		colorNodeTexture->SetScale({ 2.f,2.f });
		colorNodeTexture->nodesTest = true;
		colorNodeTextureObject->AddComponent(std::move(colorNodeTexture));
		colorNodeTextureObject->SetParent(colorNode.get());

		auto& temp = *colorNode.get();
		scene.Add(std::move(colorNode));
		scene.Add(std::move(colorNodeTextureObject));
		return temp;
	}

	GameObject& GameObjectFactory::CreateHUDScore(Scene& scene, glm::vec2& pos, int initialScore)
	{
		auto HUD = std::make_unique<dae::GameObject>();
		HUD->InitializeTransformComponent();
		HUD->SetLocalPosition(pos);
		auto hudScoreComponent = std::make_unique<dae::HUDComponent>(*HUD.get(), "Score", initialScore);
		HUD->AddComponent(std::move(hudScoreComponent));


		auto& temp = *HUD.get();
		scene.Add(std::move(HUD));
		return temp;
	}

	GameObject& GameObjectFactory::CreateHUDLives(Scene& scene, glm::vec2& pos, int initialLives)
	{
		auto HUD = std::make_unique<dae::GameObject>();
		HUD->InitializeTransformComponent();
		HUD->SetLocalPosition(pos);

		auto hudLivesComponent = std::make_unique<dae::HUDLivesComponent>(*HUD.get(), scene, initialLives);
		HUD->AddComponent(std::move(hudLivesComponent));

		auto& temp = *HUD.get();
		scene.Add(std::move(HUD));
		return temp;
	}

	GameObject& GameObjectFactory::CreateHUDLevel(Scene& scene, int initialLevel)
	{
		auto HUD = std::make_unique<dae::GameObject>();
		HUD->InitializeTransformComponent();
		HUD->SetLocalPosition(465, 450);

		std::unique_ptr<TextComponent> textComponent = std::make_unique<TextComponent>(*HUD.get(), "Level:  " + std::to_string(initialLevel), ResourceManager::GetInstance().GetFont("MInecraft.ttf", 20));
		HUD->AddComponent(std::move(textComponent));
		auto& temp = *HUD.get();
		scene.Add(std::move(HUD));
		return temp;
	}
	GameObject& GameObjectFactory::CreateHUDFPS(Scene& scene)
	{
		auto HUD = std::make_unique<dae::GameObject>();
		HUD->InitializeTransformComponent();
		HUD->SetLocalPosition(480, 10);

		auto FPSComponent = std::make_unique<dae::FPSComponent>(*HUD.get());
		HUD->AddComponent(std::move(FPSComponent));

		auto& temp = *HUD.get();
		scene.Add(std::move(HUD));
		return temp;
	}

	GameObject& GameObjectFactory::CreateHighScoreHUD(Scene& scene, int initialScore)
	{
		auto HUD = std::make_unique<dae::GameObject>();
		HUD->InitializeTransformComponent();
		HUD->SetLocalPosition(100, 450);

		std::unique_ptr<TextComponent> textComponent = std::make_unique<TextComponent>(*HUD.get(), "Highscore:  " + std::to_string(initialScore), ResourceManager::GetInstance().GetFont("Minecraft.ttf", 20));
		HUD->AddComponent(std::move(textComponent));
		auto& temp = *HUD.get();
		scene.Add(std::move(HUD));
		return temp;
	}

	GameObject& GameObjectFactory::CreatePlayerTitle(Scene& scene, int playerNumber)
	{
		auto playerTitle = std::make_unique<dae::GameObject>();
		playerTitle->InitializeTransformComponent();
		playerTitle->SetLocalPosition(10, 20);

		auto& temp = *playerTitle.get();

		if(playerNumber == 1)
		{
			playerTitle->SetLocalPosition(10, 5);
			std::unique_ptr<TextureComponent> playerTitleTexture = std::make_unique<TextureComponent>(*playerTitle.get(), "PlayerOneTitle.png");
			playerTitleTexture->SetScale({ 4.0f, 4.0f });
			playerTitle->AddComponent(std::move(playerTitleTexture));
			scene.Add(std::move(playerTitle));
		}
		else
		{
			playerTitle->SetLocalPosition(375, 5);
			std::unique_ptr<TextureComponent> playerTitleTexture = std::make_unique<TextureComponent>(*playerTitle.get(), "PlayerTwoTitle.png");
			playerTitleTexture->SetScale({ 4.0f, 4.0f });
			playerTitle->AddComponent(std::move(playerTitleTexture));
			scene.Add(std::move(playerTitle));
		}

		return temp;
	}

	GameObject& GameObjectFactory::CreateStartMenu(Scene& scene)
	{

		auto screenObject = std::make_unique<dae::GameObject>();
		screenObject->InitializeTransformComponent();
		screenObject->SetLocalPosition(0, 0);
		
		auto titleObject = std::make_unique<GameObject>();
		titleObject.get()->InitializeTransformComponent();
		titleObject.get()->SetLocalPosition(80, 80);

		auto titleTexture = std::make_unique<TextureComponent>(*titleObject.get(), "Game Title.png", 1);
		titleObject.get()->AddComponent(std::move(titleTexture));

		auto optionsObject = std::make_unique<GameObject>();
		optionsObject.get()->InitializeTransformComponent();
		optionsObject.get()->SetLocalPosition(200, 250);

		auto optionsTexture = std::make_unique<TextureComponent>(*optionsObject.get(), "Game Options.png", 1);
		optionsObject.get()->AddComponent(std::move(optionsTexture));


		optionsObject->SetParent(screenObject.get());


		auto quitObject = std::make_unique<GameObject>();
		quitObject.get()->InitializeTransformComponent();
		quitObject.get()->SetLocalPosition(290, 415);
		

		const SDL_Color color = { 255, 216, 102, 255 };
		auto font = ResourceManager::GetInstance().GetFont("Minecraft.ttf", 37);
		auto quit = std::make_unique<TextComponent>(*quitObject.get(), "Quit", font, color);
		quitObject.get()->AddComponent(std::move(quit));

		quitObject->SetParent(screenObject.get());




		auto arrowObj = std::make_unique<GameObject>();
		arrowObj->InitializeTransformComponent();
		arrowObj->SetLocalPosition(150, 250);

		auto arrowComp = std::make_unique<SelectModeComponent>(*arrowObj.get());


		auto& input = scene.GetSceneInput();
		auto movementArrow = std::make_unique<ChooseGameMode>(*arrowObj.get());
		input.AddAxisCommand(std::move(movementArrow));

		auto moveArrow = std::make_unique<ChooseGameMode>(*arrowObj.get());
		unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();
		input.AddAxisCommand(controller1, std::move(moveArrow));

		auto selectCommand = std::make_unique<SelectGameModeCommand>(*arrowObj.get());
		input.AddActionCommand(SDL_SCANCODE_RETURN, SDL_KEYDOWN, std::move(selectCommand));

		auto selectCommandPAD = std::make_unique<SelectGameModeCommand>(*arrowObj.get());
		input.AddActionCommand(controller1, Controller::ControllerButton::A, std::move(selectCommandPAD));

		arrowObj->AddComponent(std::move(arrowComp));
		arrowObj->SetParent(screenObject.get());

		titleObject->SetParent(screenObject.get());
		auto& temp = *screenObject.get();
		scene.Add(std::move(screenObject));
		scene.Add(std::move(titleObject));
		scene.Add(std::move(optionsObject));
		scene.Add(std::move(arrowObj));
		scene.Add(std::move(quitObject));
		return temp;
	}

	GameObject& GameObjectFactory::CreateGameOver(Scene& scene, GameInfoLoader& gil, int playerOneScore, int playerTwoScore)
	{
		auto mainObj = std::make_unique<dae::GameObject>();
		mainObj->InitializeTransformComponent();
		mainObj->SetLocalPosition(0, 0);

		auto gameOverObj = std::make_unique<GameObject>();
		gameOverObj->InitializeTransformComponent();
		gameOverObj->SetLocalPosition(140, 50);

		auto gameOverTexture = std::make_unique<TextureComponent>(*gameOverObj.get(), "Game Over Title.png", 1);
		gameOverObj->AddComponent(std::move(gameOverTexture));

		auto scoreTextureObj = std::make_unique<GameObject>();
		scoreTextureObj->InitializeTransformComponent();
		scoreTextureObj->SetLocalPosition(220, 250);

		auto scoreTexture = std::make_unique<TextureComponent>(*scoreTextureObj.get(), "Score.png", 1);
		scoreTextureObj->AddComponent(std::move(scoreTexture));

		auto restartObj = std::make_unique<GameObject>();
		restartObj->InitializeTransformComponent();
		restartObj->SetLocalPosition(10, 450);

		auto restartTexture = std::make_unique<TextureComponent>(*restartObj.get(), "Restart.png", 1);
		restartObj->AddComponent(std::move(restartTexture));





		auto scoreObj = std::make_unique<GameObject>();
		scoreObj->InitializeTransformComponent();
		scoreObj->SetLocalPosition(150, 320);

		auto scoreComponent = std::make_unique<FinalScoreComponent>(*scoreObj.get(), playerOneScore, playerTwoScore);
		scoreObj->AddComponent(std::move(scoreComponent));

		auto& input = scene.GetSceneInput();
		auto restartCommand = std::make_unique<ResartGame>(*scoreObj.get());
		input.AddActionCommand(SDL_SCANCODE_ESCAPE, SDL_KEYDOWN, std::move(restartCommand));

		unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();

		auto restartComd = std::make_unique<ResartGame>(*mainObj.get());
		input.AddActionCommand(controller1, Controller::ControllerButton::Y, std::move(restartComd));





		auto testGui = std::make_unique<dae::GameObject>();
		auto gui = std::make_unique<HighScoreComponent>(
			*testGui.get(),
			[&gil](const std::string& name, int score) { gil.SaveHighScore(name, score); },
			[&gil]() -> std::multimap<int, std::string, std::greater<int>> { return gil.GetHighScores(); }
		);		
		
		if (playerOneScore > playerTwoScore)
		{
			gui->SetScore(playerOneScore);
		}
		else
		{
			gui->SetScore(playerTwoScore);
		}

		testGui.get()->AddComponent(std::move(gui));
		scene.Add(std::move(testGui));




		scoreTextureObj->SetParent(mainObj.get());
		gameOverObj->SetParent(mainObj.get());
		restartObj->SetParent(mainObj.get());
		auto& temp = *gameOverObj.get();
		scene.Add(std::move(mainObj));
		scene.Add(std::move(gameOverObj));
		scene.Add(std::move(scoreTextureObj));
		scene.Add(std::move(scoreObj));
		scene.Add(std::move(restartObj));
		return temp;
	}

	GameObject& GameObjectFactory::CreateVictoryScene(Scene& scene, GameInfoLoader& gil, int playerOneScore, int playerTwoScore)
	{
		auto mainObj = std::make_unique<dae::GameObject>();
		mainObj->InitializeTransformComponent();
		mainObj->SetLocalPosition(0, 0);

		auto victoryObj = std::make_unique<GameObject>();
		victoryObj->InitializeTransformComponent();
		victoryObj->SetLocalPosition(175, 50);

		auto victoryTexture = std::make_unique<TextureComponent>(*victoryObj.get(), "Victory Title.png", 1);
		victoryObj->AddComponent(std::move(victoryTexture));

		auto scoreTextureObj = std::make_unique<GameObject>();
		scoreTextureObj->InitializeTransformComponent();
		scoreTextureObj->SetLocalPosition(220, 250);

		auto scoreTexture = std::make_unique<TextureComponent>(*scoreTextureObj.get(), "Score.png", 1);
		scoreTextureObj->AddComponent(std::move(scoreTexture));

		auto restartObj = std::make_unique<GameObject>();
		restartObj->InitializeTransformComponent();
		restartObj->SetLocalPosition(10, 450);

		auto restartTexture = std::make_unique<TextureComponent>(*restartObj.get(), "Restart.png", 1);
		restartObj->AddComponent(std::move(restartTexture));





		auto scoreObj = std::make_unique<GameObject>();
		scoreObj->InitializeTransformComponent();
		scoreObj->SetLocalPosition(150, 320);

		auto scoreComponent = std::make_unique<FinalScoreComponent>(*scoreObj.get(), playerOneScore, playerTwoScore);
		scoreObj->AddComponent(std::move(scoreComponent));

		auto& input = scene.GetSceneInput();
		auto restartCommand = std::make_unique<ResartGame>(*scoreObj.get());
		input.AddActionCommand(SDL_SCANCODE_ESCAPE, SDL_KEYDOWN, std::move(restartCommand));

		unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();

		auto restartComd = std::make_unique<ResartGame>(*mainObj.get());
		input.AddActionCommand(controller1, Controller::ControllerButton::Y, std::move(restartComd));




		auto testGui = std::make_unique<dae::GameObject>();
		auto gui = std::make_unique<HighScoreComponent>(
			*testGui.get(),
			[&gil](const std::string& name, int score) { gil.SaveHighScore(name, score); },
			[&gil]() -> std::multimap<int, std::string, std::greater<int>> { return gil.GetHighScores(); }
		);		
		
		if (playerOneScore > playerTwoScore)
		{
			gui->SetScore(playerOneScore);
		}
		else
		{
			gui->SetScore(playerTwoScore);
		}

		testGui.get()->AddComponent(std::move(gui));
		
		
		
		scene.Add(std::move(testGui));


		scoreTextureObj->SetParent(mainObj.get());
		victoryObj->SetParent(mainObj.get());
		restartObj->SetParent(mainObj.get());
		auto& temp = *victoryObj.get();
		scene.Add(std::move(mainObj));
		scene.Add(std::move(victoryObj));
		scene.Add(std::move(scoreTextureObj));
		scene.Add(std::move(scoreObj));
		scene.Add(std::move(restartObj));
		return temp;
	}

	GameObject& GameObjectFactory::CreateLevelOneTitle(Scene& scene)
	{
		auto mainObj = std::make_unique<dae::GameObject>();
		mainObj->InitializeTransformComponent();
		mainObj->SetLocalPosition(75, 150);

		auto gameTitle = std::make_unique<TextureComponent>(*mainObj.get(), "Level 01 Title.png", 1);
		mainObj->AddComponent(std::move(gameTitle));

		auto& temp = *mainObj.get();
		scene.Add(std::move(mainObj));

		return temp;
	}

	GameObject& GameObjectFactory::CreateLevelTwoTitle(Scene& scene)
	{
		auto mainObj = std::make_unique<dae::GameObject>();
		mainObj->InitializeTransformComponent();
		mainObj->SetLocalPosition(75, 150);

		auto gameTitle = std::make_unique<TextureComponent>(*mainObj.get(), "Level 02 Title.png", 1);
		mainObj->AddComponent(std::move(gameTitle));

		auto& temp = *mainObj.get();
		scene.Add(std::move(mainObj));

		return temp;
	}

	GameObject& GameObjectFactory::CreateLevelThreeTitle(Scene& scene)
	{
		auto mainObj = std::make_unique<dae::GameObject>();
		mainObj->InitializeTransformComponent();
		mainObj->SetLocalPosition(75, 150);

		auto gameTitle = std::make_unique<TextureComponent>(*mainObj.get(), "Level 03 Title.png", 1);
		mainObj->AddComponent(std::move(gameTitle));

		auto& temp = *mainObj.get();
		scene.Add(std::move(mainObj));

		return temp;
	}

	GameObject& GameObjectFactory::CreateLevelSoloInstructions(Scene& scene)
	{
		auto mainObj = std::make_unique<dae::GameObject>();
		mainObj->InitializeTransformComponent();
		mainObj->SetLocalPosition(0, 0);

		auto instructions = std::make_unique<TextureComponent>(*mainObj.get(), "InstructionsSolo.png", 1);
		instructions->SetScale({ 1.f, 1.f });
		mainObj->AddComponent(std::move(instructions));


		auto& input = scene.GetSceneInput();
		auto startCommand = std::make_unique<StartGame>(*mainObj.get());
		input.AddActionCommand(SDL_SCANCODE_RETURN, SDL_KEYDOWN, std::move(startCommand));

		auto startComd = std::make_unique<StartGame>(*mainObj.get());
		auto selectCommandPAD = std::make_unique<SelectGameModeCommand>(*mainObj.get());
		unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();
		input.AddActionCommand(controller1, Controller::ControllerButton::A, std::move(startComd));

		auto& temp = *mainObj.get();
		scene.Add(std::move(mainObj));

		return temp;
	}

	GameObject& GameObjectFactory::CreateLevelCoopInstructions(Scene& scene)
	{
		auto mainObj = std::make_unique<dae::GameObject>();
		mainObj->InitializeTransformComponent();
		mainObj->SetLocalPosition(0, 0);

		auto instructions = std::make_unique<TextureComponent>(*mainObj.get(), "InstructionsCoop.png", 1);
		mainObj->AddComponent(std::move(instructions));

		auto& input = scene.GetSceneInput();
		auto startCommand = std::make_unique<StartGame>(*mainObj.get());
		input.AddActionCommand(SDL_SCANCODE_RETURN, SDL_KEYDOWN, std::move(startCommand));

		auto startComd = std::make_unique<StartGame>(*mainObj.get());
		auto selectCommandPAD = std::make_unique<SelectGameModeCommand>(*mainObj.get());
		unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();
		input.AddActionCommand(controller1, Controller::ControllerButton::A, std::move(startComd));

		auto& temp = *mainObj.get();
		scene.Add(std::move(mainObj));

		return temp;
	}

	GameObject& GameObjectFactory::CreateLevelVSInstructions(Scene& scene)
	{
		auto mainObj = std::make_unique<dae::GameObject>();
		mainObj->InitializeTransformComponent();
		mainObj->SetLocalPosition(0, 0);

		auto instructions = std::make_unique<TextureComponent>(*mainObj.get(), "InstructionsVS.png", 1);
		mainObj->AddComponent(std::move(instructions));

		auto& input = scene.GetSceneInput();
		auto startCommand = std::make_unique<StartGame>(*mainObj.get());
		input.AddActionCommand(SDL_SCANCODE_RETURN, SDL_KEYDOWN, std::move(startCommand));

		auto startComd = std::make_unique<StartGame>(*mainObj.get());
		auto selectCommandPAD = std::make_unique<SelectGameModeCommand>(*mainObj.get());
		unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();
		input.AddActionCommand(controller1, Controller::ControllerButton::A, std::move(startComd));

		auto& temp = *mainObj.get();
		scene.Add(std::move(mainObj));

		return temp;
	}

	GameObject& GameObjectFactory::CreatePauseScreen(Scene& scene)
	{
		auto mainObj = std::make_unique<dae::GameObject>();
		mainObj->InitializeTransformComponent();
		mainObj->SetLocalPosition(0, 0);

		auto instructions = std::make_unique<TextureComponent>(*mainObj.get(), "Pause Screen.png", 1);
		mainObj->AddComponent(std::move(instructions));

		auto& input = scene.GetSceneInput();

		auto restartCommand = std::make_unique<ResartGame>(*mainObj.get());
		input.AddActionCommand(SDL_SCANCODE_ESCAPE, SDL_KEYDOWN, std::move(restartCommand));

		auto pauseCommand = std::make_unique<PauseGame>(*mainObj.get());
		input.AddActionCommand(SDL_SCANCODE_P, SDL_KEYDOWN, std::move(pauseCommand));

		unsigned int controller1 = dae::InputManager::GetInstance().GetControllerIdx();

		auto restartComd = std::make_unique<ResartGame>(*mainObj.get());
		input.AddActionCommand(controller1, Controller::ControllerButton::Y, std::move(restartComd));

		auto pauseComd = std::make_unique<PauseGame>(*mainObj.get());
		input.AddActionCommand(controller1, Controller::ControllerButton::Start, std::move(pauseComd));


		auto& temp = *mainObj.get();
		scene.Add(std::move(mainObj));

		return temp;
	}

}
