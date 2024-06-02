//#pragma once
//#include "State.h"
//#include <memory>
//#include <string>
//
//namespace dae
//{
//	class LevelState : public IState
//	{
//	public:
//		LevelState() = default;
//		LevelState(const std::string sceneName);
//		virtual ~LevelState() = default;
//		virtual void Enter() override;
//		virtual void Update() override;
//		virtual void Exit() override;
//	private:
//		std::string m_SceneName;
//	};
//
//	class LevelOne final : public LevelState
//	{
//		public:
//		LevelOne() = default;
//		LevelOne(const std::string sceneName)
//			: LevelState(sceneName) {}
//		virtual void Enter() override;
//		virtual void Update() override;
//		virtual void Exit() override;
//	};
//
//	class LevelTwo final : public LevelState
//	{
//	public:
//		LevelTwo() = default;
//		LevelTwo(const std::string sceneName)
//			: LevelState(sceneName) {}
//		virtual void Enter() override;
//		virtual void Update() override;
//		virtual void Exit() override;
//	};
//
//	class LevelThree final : public LevelState
//	{
//		public:
//		LevelThree() = default;
//		LevelThree(const std::string sceneName)
//			: LevelState(sceneName) {}
//		virtual void Enter() override;
//		virtual void Update() override;
//		virtual void Exit() override;
//	};
//
//}
//
