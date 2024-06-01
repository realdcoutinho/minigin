#include "TrashCache.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <numeric>


namespace dae
{
	TrashCache::TrashCache()
		: m_InitialSampleSize{10},
		m_x_data { 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f, 512.f, 1024.f }, //used to compile faster at start
		m_durations{ 12997.8f, 6553.62f, 4544.75f, 3663.88f, 3968, 3670.25f, 1709.5f, 1232.88f, 496, 91.5f, 78 }, //used to compile faster at start
		m_durationGO{ 61464.2f, 47963.8f, 23483.5f, 11665, 6631.12f, 2889.12f, 1558.62f, 1353.25f, 500.75f, 151.625f, 78.625f }, //used to compile faster at start
		m_durationGOAlt{ 20497.5f, 16566, 14221.6f, 12356.9f, 5770.38f, 4636.38f, 2016.25f, 1215, 518.25f, 125.625f, 60.375f } //used to compile faster at start
	{
		InitializeCalculations(m_InitialSampleSize);
		

	}

	void TrashCache::InitializeCalculations(int sampleSize)
	{
		CalculateTrashCache(sampleSize);
		CalculateTrashCacheGameObjects3D(sampleSize);
		CalculateTrashCacheGameObjects3DAlt(sampleSize);
	}

	void TrashCache::CalculateTrashCache(int sampleSize)
	{
		m_durations.clear();

		const int size = 10'000'000;
		int* arr = new int[size] {};

		for (int step = 1; step <= 1024; step *= 2)
		{
			std::vector<long long> times{};

			for (int sample{}; sample < sampleSize; ++sample)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < size; i += step)
				{
					arr[i] *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
				times.push_back(duration);
			}

			if (sampleSize > 2)
			{
				auto max_it = std::max_element(times.begin(), times.end());
				times.erase(max_it);
				auto min_it = std::min_element(times.begin(), times.end());
				times.erase(min_it);
			}


			float sum = std::accumulate(times.begin(), times.end(), 0.0f);
			float average = sum / times.size();
			


			m_durations.push_back(average);
		}

		delete[] arr;
	}

	void TrashCache::CalculateTrashCacheGameObjects3D(int sampleSize)
	{
		m_durationGO.clear();

		const int size = 10'000'000;
		GameObject3D* array = new GameObject3D[size]{};

		for (int step = 1; step <= 1024; step *= 2)
		{
			std::vector<long long> times{};

			for (int sample{}; sample < sampleSize; ++sample)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < size; i += step)
				{
					array[i].id *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

				times.push_back(duration);
			}

			if (sampleSize > 2)
			{
				auto max_it = std::max_element(times.begin(), times.end());
				times.erase(max_it);
				auto min_it = std::min_element(times.begin(), times.end());
				times.erase(min_it);
			}


			float sum = std::accumulate(times.begin(), times.end(), 0.0f);
			float average = sum / times.size();

			m_durationGO.push_back(average);
		}

		delete[] array;
	}

	void TrashCache::CalculateTrashCacheGameObjects3DAlt(int sampleSize)
	{
		m_durationGOAlt.clear();

		const int size = 10'000'000;
		GameObject3DAlt* array = new GameObject3DAlt[size]{};

		for (int step = 1; step <= 1024; step *= 2)
		{
			std::vector<long long> times{};

			for (int sample{}; sample < sampleSize; ++sample)
			{
				auto start = std::chrono::high_resolution_clock::now();
				for (int i = 0; i < size; i += step)
				{
					array[i].id *= 2;
				}
				auto end = std::chrono::high_resolution_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

				times.push_back(duration);
			}

			if (sampleSize > 2)
			{
				auto max_it = std::max_element(times.begin(), times.end());
				times.erase(max_it);
				auto min_it = std::min_element(times.begin(), times.end());
				times.erase(min_it);
			}


			float sum = std::accumulate(times.begin(), times.end(), 0.0f);
			float average = sum / times.size();

			m_durationGOAlt.push_back(average);
		}

		delete[] array;
	}
}