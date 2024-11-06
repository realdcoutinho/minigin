#include "GameInfoLoader.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include "GameInfo.h"
#include "Levels.h"

namespace fs = std::filesystem;


namespace dae
{
	GameInfoLoader::GameInfoLoader(const std::string& dataPath)
        : m_BinaryPath(dataPath + m_FilePath)
	{

        LoadGameInfo(dataPath + m_FilePath, m_LevelOneSolo, GameForm::LevelOneSolo);
		LoadGameInfo(dataPath + m_FilePath, m_LevelTwoSolo, GameForm::LevelTwoSolo);
		LoadGameInfo(dataPath + m_FilePath, m_LevelThreeSolo, GameForm::LevelThreeSolo);

        LoadGameInfo(dataPath + m_FilePath, m_LevelOneCoop, GameForm::LevelOneCoop);
        LoadGameInfo(dataPath + m_FilePath, m_LevelTwoCoop, GameForm::LevelTwoCoop);
        LoadGameInfo(dataPath + m_FilePath, m_LevelThreeCoop, GameForm::LevelThreeCoop);

        LoadGameInfo(dataPath + m_FilePath, m_LevelOneVS, GameForm::LevelOneVS);
        LoadGameInfo(dataPath + m_FilePath, m_LevelTwoVS, GameForm::LevelTwoVS);
        LoadGameInfo(dataPath + m_FilePath, m_LevelThreeVS, GameForm::LevelThreeVS);

        LoadHighScores(dataPath + m_FilePath + m_HighScoresPath);
	}

	GameInfoLoader::~GameInfoLoader()
	{
	}

	GameInfo GameInfoLoader::GetGameInfo(std::string form) const
	{
        return m_GameInfoMap.at(form);
    }

	void GameInfoLoader::LoadGameInfo(const std::string path, const std::string& filename, GameForm form)
	{
        const std::string fullPath = path + filename;
        form;

        std::ifstream inFile(fullPath, std::ios::binary);
        GameInfo gameInfo{};

        if (!inFile) {
            std::cerr << "Error opening file for reading: " << filename << std::endl;
            return /*gameInfo*/; // Return default-initialized struct
        }

        inFile.read(reinterpret_cast<char*>(&gameInfo.gameMode), sizeof(gameInfo.gameMode));
        inFile.read(reinterpret_cast<char*>(&gameInfo.level), sizeof(gameInfo.level));
        inFile.read(reinterpret_cast<char*>(&gameInfo.startColor), sizeof(gameInfo.startColor));
        inFile.read(reinterpret_cast<char*>(&gameInfo.spawnSam), sizeof(gameInfo.spawnSam));
        inFile.read(reinterpret_cast<char*>(&gameInfo.spawnCoily), sizeof(gameInfo.spawnCoily));
        inFile.read(reinterpret_cast<char*>(&gameInfo.spawnUgg), sizeof(gameInfo.spawnUgg));
        inFile.read(reinterpret_cast<char*>(&gameInfo.samInterval), sizeof(gameInfo.samInterval));
        inFile.read(reinterpret_cast<char*>(&gameInfo.coilyInterval), sizeof(gameInfo.coilyInterval));
        inFile.read(reinterpret_cast<char*>(&gameInfo.uggInterval), sizeof(gameInfo.uggInterval));
       
        inFile.read(reinterpret_cast<char*>(&gameInfo.discOne), sizeof(gameInfo.discOne));
        inFile.read(reinterpret_cast<char*>(&gameInfo.discTwo), sizeof(gameInfo.discTwo));
        inFile.read(reinterpret_cast<char*>(&gameInfo.discThree), sizeof(gameInfo.discThree));


        inFile.close();

        //the files string end in .bin. We remove this to get the name of the level
        std::string levelName = filename.substr(0, filename.size() - 4);
        m_GameInfoMap[levelName] = gameInfo;
	}

    void GameInfoLoader::LoadHighScores(const std::string& filename)
    {
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) {
            std::cerr << "File not found. A new file will be created upon saving scores." << std::endl;
            return;  // Exit if file does not exist
        }

        char name[256];
        int score;
        char checkChar;

        while (inFile.read(&checkChar, sizeof(checkChar))) {
            if (checkChar == 'n') {
                inFile.read(name, 256);
                if (inFile.read(&checkChar, sizeof(checkChar)) && checkChar == 's') {
                    inFile.read(reinterpret_cast<char*>(&score), sizeof(score));
                    m_HighScores.insert({ score, std::string(name) });
                }
            }
        }

        inFile.close();
    }

    void GameInfoLoader::SaveHighScore(const std::string& name, int score)
    {
        const std::string fullPath = m_BinaryPath + m_HighScoresPath; // Full path to the high score file
        // Open the file in binary mode for appending
        std::ofstream outFile(fullPath, std::ios::binary | std::ios::app);
        if (!outFile) {
            std::cerr << "Error: Could not open file for writing at " << fullPath << std::endl;
            return;
        }

        outFile.put('n'); // Write the 'n' character to indicate the start of a name

        char nameBuffer[256] = {}; // Create a buffer to ensure we write exactly 256 bytes
        strncpy_s(nameBuffer, sizeof(nameBuffer), name.c_str(), sizeof(nameBuffer) - 1); // Copy the name to the buffer safely
        outFile.write(nameBuffer, sizeof(nameBuffer)); // Write the name array to the file

        outFile.put('s'); // Write the 's' character to indicate the start of a score
        outFile.write(reinterpret_cast<const char*>(&score), sizeof(score)); // Write the integer score as binary

        outFile.close(); // Close the file after writing
    }

    int GameInfoLoader::GetHighestScore() const
    {
        if (!m_HighScores.empty()) {
            return m_HighScores.begin()->first; // The first element in the map has the highest score
        }
        return 0; // Return 0 if no scores are loaded
    }
    std::multimap<int, std::string, std::greater<int>> GameInfoLoader::GetHighScores()
    {
        LoadHighScores(m_BinaryPath + m_HighScoresPath);
        return m_HighScores;
    }
}
