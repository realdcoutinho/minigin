#pragma once
#include "GameObject.h"
#include "Controller.h"
#include <glm/glm.hpp>
#include "MovementComponent.h"
#include <SDL.h>
#include "Subject.h"
#include "CharacterComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
#include "AudioSystem.h"
#include "Command.h"
#include "TriangularGrid.h"
#include "GridNavigator.h"
#include "QBertCharacterComponent.h"
#include "EnemyCharacterComponent.h"
#include "GridNavigator.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Timer.h"
#include "TimeManager.h"
#include "SelectModeComponent.h"
#include "GameOverComponent.h"
#include "GameMode.h"
#include "GameModeManager.h"
#include "QBertGameMode.h"



namespace dae
{
	class Controller;


	class SelectModeCommand : public Command
	{
	public:
		SelectModeCommand() = default;

		virtual void Execute()
		{
			SceneManager::GetInstance().SetActiveScene("IntructionsScene");
		}
	};


	class MuteAllSounds : public Command
	{
	public:
		MuteAllSounds() = default;

		virtual void Execute()
		{
			auto& ss = ServiceLocator::GetAudioService();
			ss.get()->Mute();
		}
	};

	class ReduceSound : public Command
	{
	public:
		ReduceSound() = default;

		float m_decrease = -0.1f;

		virtual void Execute()
		{
			auto& ss = ServiceLocator::GetAudioService();
			ss.get()->SetVolume(m_decrease);
		}
	};

	class IncreaseSound : public Command
	{
	public:
		IncreaseSound() = default;

		float m_increase = 0.1f;

		virtual void Execute()
		{
			auto& ss = ServiceLocator::GetAudioService();
			ss.get()->SetVolume(m_increase);
		}
	};


	class GameObjectCommand : public Command
	{
	public:
		GameObjectCommand(GameObject& pActor)
			: m_pActor(pActor)
		{}

		virtual void Execute() = 0;

	protected:
		GameObject* GetActor() const { return &m_pActor; }
	private:
		GameObject& m_pActor;
	};




	class MovementCommand : public GameObjectCommand
	{
	public:

		MovementCommand(GameObject& pActor, glm::vec2& dir) :
			GameObjectCommand(pActor),
			m_directionVector{ dir }
		{};

		glm::vec2 m_directionVector;


		void Execute()
		{
			if(!GetActor()->GetComponent<GridNavigator>()->IsMoving())
				MoveActor(m_directionVector);

		}

		void SetDirection(glm::vec2& dir)
		{
			m_directionVector = dir;
		}

	private:
		void MoveActor(glm::vec2 dir)
		{
			GetActor()->GetComponent<MovementComponent>()->Move(dir);
			GetActor()->GetComponent<CharacterComponent>()->HandleInput(dir);
		}
	};



	class CommandAxis
	{
	public:
		virtual ~CommandAxis() = default;

		virtual void Execute() = 0;
		virtual void SetDirection(glm::vec2 direction) = 0;
	};

	class SelectionCommand : public CommandAxis
	{
	public:
		SelectionCommand(GameObject& select, float pos1, float pos2, float pos3)
			: m_pos1(pos1),
			m_pos2(pos2),
			m_pos3(pos3),
			m_curPos(pos1),
			m_pSelect(select)
		{}

		virtual void Execute()
		{
			auto pos = m_pSelect.GetLocalPosition();
			const glm::vec2 pos1 = { pos.x, m_curPos };
			m_pSelect.SetLocalPosition(pos1);
		};

		virtual void SetDirection(glm::vec2 direction)
		{
			float y = direction.y;
			if (y < 0)
				//Select Up
			{
				if (m_curPos == m_pos1)
				{
					m_curPos = m_pos3;
				}
				else if (m_curPos == m_pos2)
				{
					m_curPos = m_pos1;
				}
				else if (m_curPos == m_pos3)
				{
					m_curPos = m_pos2;
				}
			}
			else if (y > 0)
				//Select Down
			{
				if (m_curPos == m_pos1)
				{
					m_curPos = m_pos2;
				}
				else if (m_curPos == m_pos2)
				{
					m_curPos = m_pos3;
				}
				else if (m_curPos == m_pos3)
				{
					m_curPos = m_pos1;
				}
			}
		}
		
		float m_pos1;
		float m_pos2;
		float m_pos3;
		float m_curPos;
		GameObject& m_pSelect;
	};


	class GameObjectCommandAxis : public CommandAxis
	{
	public:
		GameObjectCommandAxis(GameObject& pActor)
			: m_pActor(pActor)
		{}

		virtual void Execute() = 0;
		virtual void SetDirection(glm::vec2 direction) = 0;

	protected:
		GameObject* GetActor() const { return &m_pActor; }
	private:
		GameObject& m_pActor;
	};


	class MovementCommandAxis : public GameObjectCommandAxis
	{
	public:

		MovementCommandAxis(GameObject& pActor) :
			GameObjectCommandAxis(pActor),
			m_directionVector{}
		{};

		glm::vec2 m_directionVector;


		void Execute()
		{
			MoveActor(m_directionVector);
		}

		void SetDirection(glm::vec2 direction)
		{
			m_directionVector = direction;
		}


	private:
		void MoveActor(glm::vec2 dir)
		{
			GetActor()->GetComponent<MovementComponent>()->Move(dir);
			GetActor()->GetComponent<CharacterComponent>()->HandleInput(dir);

		}

	};


	class ChooseGameMode : public GameObjectCommandAxis
	{
		public:
			ChooseGameMode(GameObject& pActor)
				: GameObjectCommandAxis(pActor)
				, m_directionVector{ 0,0 }
			{
			};

		glm::vec2 m_directionVector;

		void Execute()
		{
			MoveActor(m_directionVector);
		}

		void MoveActor(glm::vec2 dir)
		{
			if (dir.x == 0 && dir.y == 0)
				return;

			glm::vec2 loc = { dir.x, -dir.y };

			auto actor = GetActor();
			actor->GetComponent<SelectModeComponent>()->HandleInput(loc);

		}

		void SetDirection(glm::vec2 direction)
		{
			m_directionVector = direction;
		}
	};



	class SelectGameModeCommand : public GameObjectCommand
	{
	public:
		SelectGameModeCommand(GameObject& pActor)
			: GameObjectCommand(pActor)
		{};
			virtual void Execute()
		{
			GetActor()->GetComponent<SelectModeComponent>()->SelectMode();
		}
	};

	class ResartGame : public GameObjectCommand
	{
	public:
		ResartGame(GameObject& pActor)
			: GameObjectCommand(pActor)
		{};
		virtual void Execute()
		{
			auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
			auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
			if (qbertGameMode)
				qbertGameMode->Restart();
		}
	};

	class StartGame : public GameObjectCommand
	{
	public:
		StartGame(GameObject& pActor)
			: GameObjectCommand(pActor)
		{};
		virtual void Execute()
		{
			auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
			auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
			if (qbertGameMode)
				qbertGameMode->StartGame();
		}
	};

	class PauseGame : public GameObjectCommand
	{
	public:
		PauseGame (GameObject& pActor)
			: GameObjectCommand(pActor)
		{};
		virtual void Execute()
		{
			auto gameMode = GameModeManager::GetInstance().GetActiveGameMode();
			auto qbertGameMode = dynamic_cast<QBertGameMode*>(gameMode);
			if (qbertGameMode)
				qbertGameMode->PauseGame();
		}
	};


	class GridMovement : public GameObjectCommandAxis
	{
	public:
		GridMovement(GameObject& pActor)
			: GameObjectCommandAxis(pActor)
			, m_directionVector{}
		{

		};

		glm::vec2 m_directionVector;
		float m_Interval = 0.2f;
		float lastTime = -99999999.0f;


		void Execute()
		{
			float currentTime = SceneManager::GetInstance().GetActiveScene().GetTimer().GetTotalTime();
			if (currentTime - lastTime  > m_Interval)
			{
				lastTime = currentTime;
				MoveActor(m_directionVector);


			}
			//MoveActor(m_directionVector);
		}

		void MoveActor(glm::vec2 dir)
		{
			if (dir.x == 0 && dir.y == 0)
				return;

			glm::vec2 loc = { dir.x, -dir.y };

			auto actor = GetActor();
			auto charComp = actor->GetComponent<CharacterComponent>();
			if(charComp)
				charComp->HandleInput(loc);
			auto movement = actor->GetComponent<GridNavigator>();
			if(movement)
				movement->MoveToDirection(loc);
		}


		void SetDirection(glm::vec2 direction)
		{
			m_directionVector = direction;
		}
	};


}

