#pragma once
#include <memory>
#include <vector>

#include "BaseComponent.h"

namespace dae
{
	class TrashCache;

	class PlotGraphComponent : public BaseComponent
	{
	public:
		PlotGraphComponent(GameObject& pOwner);
		~PlotGraphComponent();
		void Render();
		void Update() override;
	private:

		void Exercise1();
		void Exercise2();

		void PlotGraph(std::vector<float>& ydata);
		void PlotGraphs(std::vector<std::vector<float>>& ydata);

		std::unique_ptr<TrashCache> m_TrashCache;
	};


}
