#pragma once
#include "BaseComponent.h"
#include <functional>
#include <map>
#include <string> // Include this to use std::string

namespace dae
{
    class HighScoreComponent final : public BaseComponent
    {
    public:
        HighScoreComponent(GameObject& pOwner,
            std::function<void(const std::string&, int)> saveFunc,
            std::function<std::multimap<int, std::string, std::greater<int>>()> getScoresFunc);

        ~HighScoreComponent() override = default;

        void Render() override;
        void Update() override;

        void SetScore(int score) { m_Score = score; }

    private:
        int m_Score;
        bool m_HighScoreChanged{ false };
        bool m_IsScoreSaved{ false };
        char m_PlayerNameBuffer[256]{};

        // Proper declaration using std::function with fully specified types
        std::function<void(const std::string&, int)> m_SaveHighScoreFunc;
        std::function<std::multimap<int, std::string, std::greater<int>>()> m_GetHighScoresFunc;

        std::multimap<int, std::string, std::greater<int>> m_HighScores;
    };
}
