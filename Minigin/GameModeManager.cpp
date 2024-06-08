#include "GameModeManager.h"
#include "GameMode.h"

namespace dae
{
	void GameModeManager::Update(float elapsed)
	{
		if(m_ActiveGameMode != nullptr)
			m_ActiveGameMode->Update(elapsed);
	}

	bool GameModeManager::IsGameRunning()
	{
		if (m_ActiveGameMode != nullptr)
			return m_ActiveGameMode->IsGameRunning();
		else
			return false;
	}
}
