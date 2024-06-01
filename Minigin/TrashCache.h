#pragma once
#include <vector>

namespace dae 
{
	struct transform
	{
		float matric[16] = { 1, 0, 0, 0,
								 0, 1, 0, 0,
								 0, 0, 1, 0,
								 0, 0, 0, 1 };
	};

	class GameObject3D
	{
	public:
		transform local{};
		int id{};
	};

	class GameObject3DAlt
	{
	public:
		transform* local{};
		int id{};
	};

	class TrashCache
	{	
		public:
		TrashCache();


		void CalculateTrashCache(int sampleSize);
		void CalculateTrashCacheGameObjects3D(int sampleSize);
		void CalculateTrashCacheGameObjects3DAlt(int sampleSize);

		std::vector<float>& GetXData() { return m_x_data; }
		std::vector<float>& GetDurations() { return m_durations; }
		std::vector<float>& GetDurationGO() { return m_durationGO; }
		std::vector<float>& GetDurationGOAlt() { return m_durationGOAlt; }

	private:

		void InitializeCalculations(int sampleSize);
		int m_InitialSampleSize{};
		std::vector<float> m_x_data;
		std::vector<float> m_durations;
		std::vector<float> m_durationGO;
		std::vector<float> m_durationGOAlt;

	};
}


