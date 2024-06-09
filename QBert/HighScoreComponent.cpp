#include "HighScoreComponent.h"
#include "imgui.h"
#include "GameObject.h"
#include "backends/imgui_impl_sdl2.h"
#include <iostream>
#include <cstring> // Use <cstring> for string operations if needed

namespace dae
{
    HighScoreComponent::HighScoreComponent(GameObject& pOwner,
        std::function<void(const std::string&, int)> saveFunc,
        std::function<std::multimap<int, std::string, std::greater<int>>()> getScoresFunc)
        : BaseComponent(pOwner), m_SaveHighScoreFunc(saveFunc), m_GetHighScoresFunc(getScoresFunc)
    {
        m_HighScores = m_GetHighScoresFunc();
    }

    void HighScoreComponent::Render()
    {
        ImGui_ImplSDL2_NewFrame();
        //ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(472.5f, 10));
        ImGui::SetNextWindowSize(ImVec2(160, 275));
        ImGui::Begin("Leaderboard", nullptr, ImGuiWindowFlags_NoResize);

        ImGui::Text("Input your name:");
        ImGui::InputText("Name", m_PlayerNameBuffer, sizeof(m_PlayerNameBuffer));
        if (ImGui::Button("Save Score", ImVec2(128.f, 24.f)))
        {
            //if (!m_IsScoreSaved)
            //{
            //    m_IsScoreSaved = true;
                std::cout << "Save Score button pressed" << std::endl;
                //print name and score
                std::cout << "Name: " << m_PlayerNameBuffer << std::endl;
                std::cout << "Score: " << m_Score << std::endl;
                    m_SaveHighScoreFunc(m_PlayerNameBuffer, m_Score);
                    m_HighScores = m_GetHighScoresFunc();
        }

        // Display each entry in the high scores multimap
        int rank = 1;
        for (auto it = m_HighScores.begin(); it != m_HighScores.end(); ++it, ++rank)
        {
            std::string leaderboardEntry = std::to_string(rank) + ". " + it->second + " - " + std::to_string(it->first);
            ImGui::Text("%s", leaderboardEntry.c_str());
        }

        ImGui::End();
        ImGui::Render();
    }

    void HighScoreComponent::Update()
    {
        // Implement update logic if necessary
    }
}
