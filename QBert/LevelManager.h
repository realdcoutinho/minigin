#pragma once
#include <memory>
#include "Singleton.h"
#include <vector>

namespace dae
{
	class TriangularGrid;
	class GridNode;
	class GameObject;
	class GridNavigator;
	class CoilyComponent;
	class LevelManager final : public Singleton<LevelManager>
	{
	public:
		TriangularGrid& GetGrid() const { return *m_pGrid; }
		void SetGrid(TriangularGrid* pGrid) { m_pGrid = pGrid; }

		void SetCurrentQbertNode(GridNode* pNode);
		GridNode& GetCurrentQbertNode() const { return *m_CurrentQbertNode; }

		void SetCoily(CoilyComponent* pCoily) { m_pCoilies.push_back(pCoily); }

	private:
		friend class Singleton<LevelManager>;
		LevelManager() = default;

		TriangularGrid* m_pGrid;
		GridNode* m_CurrentQbertNode;
		CoilyComponent* m_pCoily;

		std::vector<CoilyComponent*> m_pCoilies;
	};
}


