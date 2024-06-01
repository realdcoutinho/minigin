#pragma once
#include "GameModeManager.h"
namespace dae
{
	class GameMode
	{
		template <typename T, typename std::enable_if<std::is_base_of<GameMode, T>::value>::type*>
		friend GameMode& GameModeManager::CreateGameMode(const std::string& name);

	public:
		virtual void Update(float elapsed) = 0;
		virtual ~GameMode() = default;
	};

}

