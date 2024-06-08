#include "ResourceLoader.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"

#include <memory>

namespace dae
{
	ResourceLoader::ResourceLoader()
	{
		LoadResources();
	}

	ResourceLoader::~ResourceLoader()
	{

	}

	void ResourceLoader::LoadResources()
	{
		auto& resourceManager = ResourceManager::GetInstance();
		LoadTextures(resourceManager);
		LoadFonts(resourceManager);
		LoadAudio(resourceManager);
	}

	void ResourceLoader::LoadFonts(ResourceManager& rm)
	{
		rm.GetFont("Minecraft.ttf", 17);
		rm.GetFont("Lingua.otf", 17);
	}

	void ResourceLoader::LoadAudio(ResourceManager& rm)
	{
		//rm.GetSound("overworld.wav"); //they need to be initialized in a psecific order
		//rm.GetSound("wow.wav");
		//rm.GetSound("brickBreak.wav");

		rm.GetSound(m_FilePath + "Change Selection.wav");
		rm.GetSound(m_FilePath + "Clear Disks.wav");
		rm.GetSound(m_FilePath + "Coily Egg Jump.wav");
		rm.GetSound(m_FilePath + "Coily Fall.wav");
		rm.GetSound(m_FilePath + "Coily Snake Jump.wav");
		rm.GetSound(m_FilePath + "Demo Sound.wav");
		rm.GetSound(m_FilePath + "Disk Land.wav");
		rm.GetSound(m_FilePath + "Disk Lift.wav");
		rm.GetSound(m_FilePath + "Level Screen Tune.wav");
		rm.GetSound(m_FilePath + "Other Foes Jump.wav");
		rm.GetSound(m_FilePath + "QBert Fall.wav");
		rm.GetSound(m_FilePath + "QBert Hit.wav");
		rm.GetSound(m_FilePath + "QBert Jump.wav");
		rm.GetSound(m_FilePath + "Round Complete Tune.wav");
		rm.GetSound(m_FilePath + "SlickSamCaught.wav");
		rm.GetSound(m_FilePath + "Sweating.wav");








	}

	void ResourceLoader::LoadTextures(ResourceManager& rm)
	{
		rm.GetTexture("Heart.png");
		rm.GetTexture("Qbert Cubes.png");
		rm.GetTexture("Active.png");
		rm.GetTexture("Game Title.png");
		rm.GetTexture("Game Options.png");
		rm.GetTexture("Selection Arrow.png");
		rm.GetTexture("P1 Controls.png");

		rm.GetTexture("InstructionsSolo.png");
		rm.GetTexture("InstructionsCoop.png");
		rm.GetTexture("InstructionsVS.png");

		rm.GetTexture("Pause Screen.png");
		rm.GetTexture("Victory Title.png");

		rm.GetTexture("Game Over Title.png");

		rm.GetTexture("Level 01 Title.png");
		rm.GetTexture("Level 02 Title.png");
		rm.GetTexture("Level 03 Title.png");

		rm.GetTexture("Score.png");
		rm.GetTexture("Restart.png");


		
		rm.GetTexture("P2 QBert Controls.png");

		rm.GetTexture("Coily Spritesheet.png");
		rm.GetTexture("Qbert P1 Spritesheet.png");
		rm.GetTexture("Qbert P2 Spritesheet.png");
		rm.GetTexture("Disk Spritesheet.png");
		rm.GetTexture("SamSprite.png");
		rm.GetTexture("SlickSprite.png");

		rm.GetTexture("Ugg.png");
		rm.GetTexture("Wrongway.png");

		rm.GetTexture("Egg.png");
		rm.GetTexture("NodeTexturesLevelOne.png");
		rm.GetTexture("NodeTexturesLevelTwo.png");

	}
}

