#pragma once
namespace dae
{
	struct GameInfo
	{
		int gameMode = 0;
		int level = 0;
		int startColor = 0;
		bool spawnSam = false;
		bool spawnCoily = false;
		bool spawnUgg = false;
		float samInterval = 0.0f;
		float coilyInterval = 0.0f;
		float uggInterval = 0.0f;
		int discOne = 0;
		int discTwo = 0;
		int discThree = 0;
	};
}