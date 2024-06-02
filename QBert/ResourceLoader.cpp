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
		rm.GetSound("overworld.wav"); //they need to be initialized in a psecific order
		rm.GetSound("wow.wav");
		rm.GetSound("brickBreak.wav");
	}

	void ResourceLoader::LoadTextures(ResourceManager& rm)
	{
		rm.GetTexture("Heart.png");
		rm.GetTexture("Qbert Cubes.png");
		rm.GetTexture("Active.png");
		rm.GetTexture("Game Title.png");
		rm.GetTexture("P1 Controls.png");

		
		rm.GetTexture("P2 QBert Controls.png");

		rm.GetTexture("Coily Spritesheet.png");
		rm.GetTexture("Qbert P1 Spritesheet.png");
		rm.GetTexture("Qbert P2 Spritesheet.png");
		rm.GetTexture("Disk Spritesheet.png");
		rm.GetTexture("SamSprite.png");
		rm.GetTexture("SlickSprite.png");
		rm.GetTexture("Egg.png");
		rm.GetTexture("NodeTexturesLevelOne.png");
		rm.GetTexture("NodeTexturesLevelTwo.png");

	}
}

