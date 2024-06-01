#pragma once
#include <memory>
#include <string>
#include <map>

namespace dae
{



	struct GameInfo;
	enum class GameForm;
	class GameInfoLoader final
	{
	public:
		GameInfoLoader(const std::string& dataPath);
		~GameInfoLoader();

		GameInfoLoader(const GameInfoLoader& other) = delete;
		GameInfoLoader(GameInfoLoader&& other) = delete;
		GameInfoLoader& operator=(const GameInfoLoader& other) = delete;
		GameInfoLoader& operator=(GameInfoLoader&& other) = delete;
		
		GameInfo GetGameInfo(std::string form) const;
		void LoadGameInfo(const std::string path, const std::string& filename, GameForm form);

	private:
		const std::string m_FilePath = "LevelData/";

		const std::string m_LevelOneSolo = "LevelOneSolo.bin";
		const std::string m_LevelTwoSolo = "LevelTwoSolo.bin";
		const std::string m_LevelThreeSolo = "LevelThreeSolo.bin";

		const std::string m_LevelOneCoop = "LevelOneCoop.bin";
		const std::string m_LevelTwoCoop = "LevelTwoCoop.bin";
		const std::string m_LevelThreeCoop = "LevelThreeCoop.bin";

		const std::string m_LevelOneVS = "LevelOneVS.bin";
		const std::string m_LevelTwoVS = "LevelTwoVS.bin";
		const std::string m_LevelThreeVS = "LevelThreeVS.bin";


		std::map<std::string, GameInfo> m_GameInfoMap;
	};
}


