//#pragma once
//#include "BaseComponent.h"
//#include <string>
//#include "Event.h"
//
//namespace dae
//{
//	//class ISubject;
//	class IObserver;
//	class ScoreComponent : public BaseComponent
//	{
//	public:
//		ScoreComponent(GameObject& pOwner, int intialPoints = 0);
//		~ScoreComponent();
//
//		ScoreComponent(const ScoreComponent& other) = delete;
//		ScoreComponent(ScoreComponent&& other) noexcept = delete;
//		ScoreComponent& operator=(const ScoreComponent& other) = delete;
//		ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;
//
//		void Render() override;
//		void Update() override;
//
//		void SetScore(int score);
//		int GetScore() const;
//
//	private:
//		int m_Score{};
//		//std::unique_ptr<ISubject> m_Subject;
//	};
//
//
//}
//
