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

        inFile.close();

        //the files string end in .bin. We remove this to get the name of the level
        std::string levelName = filename.substr(0, filename.size() - 4);
        m_GameInfoMap[levelName] = gameInfo;
	}

}
