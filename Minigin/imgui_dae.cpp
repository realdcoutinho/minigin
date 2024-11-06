#include "imgui_dae.h"
#include "imgui.h"
#include <iostream>
#include <algorithm>
#include <chrono>
#include <vector>
#include <numeric>
#include "TrashCache.h"

#include "imgui.h"
#include "imgui_plot.h"
#include "backends/imgui_impl_opengl2.h"
#include "backends/imgui_impl_sdl2.h"
#include "implot.h"

namespace dae
{
	imgui_dae::imgui_dae()
	{

	}

	imgui_dae::~imgui_dae()
	{

	}

	void imgui_dae::Init(SDL_Window* window, SDL_GLContext context)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplSDL2_InitForOpenGL(window, context);
		ImGui_ImplOpenGL2_Init();

		//ImPlot::CreateContext()
		//CalculateTrashCache(initialSampleSize);
		//CalculateTrashCacheGameObjects3D(initialSampleSize);
		//CalculateTrashCacheGameObjects3DAlt(initialSampleSize);
		//m_x_data = { 1.f, 2.f, 4.f, 8.f, 16.f, 32.f, 64.f, 128.f, 256.f, 512.f, 1024.f };

		m_TrashCache = std::make_unique<TrashCache>();
	}

	void imgui_dae::Render()
	{
		ImGui_ImplOpenGL2_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		Exercise1();
		Exercise2(); 

		//ImPlot::ShowDemoWindow();

		ImGui::Render();
		ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	}

	void imgui_dae::Destroy()
	{
		ImGui_ImplOpenGL2_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
	}

	void imgui_dae::Exercise1()
	{
		ImGui::Begin("Exercise 1", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		static int samples = 1;
		ImGui::SliderInt("# sample", &samples, 1, 20);


		static int clicked = 0;
		if (ImGui::Button("Trash The Cash"))
			clicked++;
		if (clicked & 1)
		{
			clicked++;
			m_TrashCache->CalculateTrashCache(samples);
		}

		PlotGraph(m_TrashCache->GetDurations());

		ImGui::End();
	}


	void imgui_dae::Exercise2()
	{
		ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

		static int samples = 1;
		ImGui::SliderInt("# sample", &samples, 1, 20);


		static int go3d = 0;
		if (ImGui::Button("Trash The Cash Game Objects 3D"))
			go3d++;
		if (go3d & 1)
		{
			go3d++;
			m_TrashCache->CalculateTrashCacheGameObjects3D(samples);
		}

		PlotGraph(m_TrashCache->GetDurationGO());

		static int go3dalt = 0;
		if (ImGui::Button("Trash The Cash Game Objects 3DAlt"))
			go3dalt++;
		if (go3dalt & 1)
		{
			go3dalt++;
			m_TrashCache->CalculateTrashCacheGameObjects3DAlt(samples);
		}

		PlotGraph(m_TrashCache->GetDurationGOAlt());

		std::vector<std::vector<float>> combined;
		combined.push_back(m_TrashCache->GetDurationGO());
		combined.push_back(m_TrashCache->GetDurationGOAlt());

		ImGui::Text("Combined:");

		PlotGraphs(combined);
	
		ImGui::End();

	}

	void imgui_dae::PlotGraph(std::vector<float>& ydata)
	{
		if (m_TrashCache->GetXData().size() != ydata.size())
		{
			std::cout << "xdata and ydata are not the same size" << std::endl;
			return;
		}
		if (m_TrashCache->GetXData().size() == 0 || ydata.size() == 0)
		{
			std::cout << "xdata and ydata are empty" << std::endl;
			return;
		}

		static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
		static uint32_t selection_start = 0, selection_length = 0;

		//render plot ex 1
		ImGui::PlotConfig config;
		config.values.xs = m_TrashCache->GetXData().data();
		config.values.count = static_cast<int>(ydata.size() + 1);
		config.values.ys = ydata.data();
		config.values.ys_count = 11;
		config.values.colors = colors;
		config.scale.min = 0;

		auto max_it = std::max_element(ydata.begin(), ydata.end());
		float element = *max_it;
		float interval = element / 10;

		config.scale.max = element + interval;
		config.tooltip.show = true;
		config.tooltip.format = "steps=%.2f, microseconds=%.2f";
		config.grid_x.show = false;
		config.grid_x.size = 50;
		config.grid_x.subticks = 4;
		config.grid_y.show = true;
		config.grid_y.size = element/ 10.0f;
		config.grid_y.subticks = 10;
		config.selection.show = false;
		config.selection.start = &selection_start;
		config.selection.length = &selection_length;
		config.frame_size = ImVec2(250, 150);
		ImGui::Plot("plot1", config);
	}

	void imgui_dae::PlotGraphs(std::vector<std::vector<float>>& ydata)
	{

		float max_value = std::numeric_limits<float>::lowest();
		for (const auto& vec : ydata) 
		{
			if (!vec.empty()) 
			{
				float local_max = *std::max_element(vec.begin(), vec.end());
				max_value = std::max(max_value, local_max);
			}
		}
		float interval = max_value / 10;

		const float* y_data[] = { ydata[0].data(), ydata[1].data() };
		static ImU32 colors[3] = { ImColor(0, 255, 0), ImColor(255, 0, 0), ImColor(0, 0, 255) };
		static uint32_t selection_start = 0, selection_length = 0;


		ImGui::PlotConfig conf;
		conf.values.xs = m_TrashCache->GetXData().data();
		conf.values.count = 12;
		conf.values.ys_list = y_data; // use ys_list to draw several lines simultaneously
		conf.values.ys_count = 2;
		conf.values.colors = colors;
		conf.scale.min = 0;



		conf.scale.max = max_value + interval;
		conf.tooltip.show = true;
		conf.tooltip.format = "steps=%.2f, microseconds=%.2f";
		conf.grid_x.show = false;
		conf.grid_x.size = 50;
		conf.grid_x.subticks = 4;
		conf.grid_y.show = true;
		conf.grid_y.size = max_value/ 10.0f;
		conf.grid_y.subticks = 10;
		conf.selection.show = false;
		conf.selection.start = &selection_start;
		conf.selection.length = &selection_length;
		conf.frame_size = ImVec2(250, 150);
		ImGui::Plot("plot1", conf);
	}
}