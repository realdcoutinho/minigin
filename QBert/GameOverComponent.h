#pragma once
#include "BaseComponent.h"
#include <string>
#include "GameObject.h"

namespace dae
{
	class TextureComponent;
	class TextComponent;
	class QBertGameMode;
	class GameOverComponent final : public dae::BaseComponent
	{
	public:
		GameOverComponent(dae::GameObject& pOwner, int score1, int score2);
		virtual ~GameOverComponent() = default;


		virtual void Render() override;
		virtual void Update() override;
	
		void RestartGame();
	
	private:
		
		int m_Score1;
		int m_Score2;
		const std::string m_Player1 = "Player 1";
		const std::string m_Player2 = "Player 2";

		TextureComponent* m_pScore;
		TextComponent* m_pTextPlayerOne;
		TextComponent* m_pTextPlayerTwo;
		QBertGameMode* m_pGameMode;
	};
}



