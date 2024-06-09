
#include <SDL.h>


#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>

#include <SDL_mixer.h>

#endif
#endif

#include "Minigin.h"
#include "GameLauncher.h"



void load()
{
	
}

int main(int, char*[]) 
{
	dae::Minigin engine("../Data/");

	std::unique_ptr<dae::GameLauncher> launcher = std::make_unique<dae::GameLauncher>();

	engine.Run(/*load*/);
    
	return 0;
}