#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <memory>

namespace dae
{	
	class GameMode;
	class GameModeManager final : public Singleton<GameModeManager>
	{
	public:


		template <typename T, typename std::enable_if<std::is_base_of<GameMode, T>::value>::type* = nullptr>
		GameMode& CreateGameMode(const std::string& name);

		void SetActiveGameMode(GameMode* gameMode);
		GameMode* GetActiveGameMode() const { return m_ActiveGameMode; }

		void Update(float elapsed);
	private:
		friend class Singleton<GameModeManager>;
		GameModeManager() = default;

		std::vector<std::shared_ptr<GameMode>> m_GameModes;
		GameMode* m_ActiveGameMode;


	};

	template <typename T, typename std::enable_if<std::is_base_of<GameMode, T>::value>::type*>
	GameMode& GameModeManager::CreateGameMode(const std::string& name)
	{
		auto gameMode = std::make_shared<T>(name);
		m_ActiveGameMode = gameMode.get();
		m_GameModes.push_back(std::move(gameMode));
		return *m_ActiveGameMode;
	}

}

