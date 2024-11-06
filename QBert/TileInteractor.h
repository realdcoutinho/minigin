//#pragma once
//#include "BaseComponent.h"
//#include "Observer.h"
//#include "BaseEvent.h"
//namespace dae
//{
//	class GridNode;
//	class TriangularGrid;
//	class TileInteractor : public BaseComponent, public IObserver
//	{
//	public:
//		TileInteractor(GameObject& pOwner, TriangularGrid& pGrid,  unsigned int subID);
//		~TileInteractor();
//
//		TileInteractor(const TileInteractor&) = delete;
//		TileInteractor(TileInteractor&&) = delete;
//		TileInteractor& operator= (const TileInteractor&) = delete;
//		TileInteractor& operator= (const TileInteractor&&) = delete;
//
//		void Render() override;
//		void Update() override;
//
//
//		virtual void OnNotify(BaseEvent* event);
//
//	private:
//
//		GridNode* m_CurrentTile;
//		TriangularGrid* m_pGrid;
//
//		size_t m_TotalNumberTiles{ 0 };
//		size_t m_CurrentSetTiles{ 0 };
//	};
//
//}
//
