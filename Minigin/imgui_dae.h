#pragma once

#include <vector>
#include <SDL.h>
#include <memory>


namespace dae
{
	class TrashCache;

	class imgui_dae
	{
	public:
		imgui_dae();
		~imgui_dae();


		void Init(SDL_Window* window, SDL_GLContext context);
		void Render();
		void Destroy();


	private:
		void Exercise1();
		void Exercise2();

		void PlotGraph(std::vector<float>& ydata);
		void PlotGraphs(std::vector<std::vector<float>>& ydata);

		std::unique_ptr<TrashCache> m_TrashCache;
	};
}

