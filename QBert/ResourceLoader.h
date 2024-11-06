#pragma once
#include <string>
namespace dae
{
	class ResourceManager;
	class SceneManager;
	class ResourceLoader final
	{
	public:
		ResourceLoader();
		~ResourceLoader();

	private:
		void LoadResources();
		void LoadFonts(ResourceManager& rm);
		void LoadAudio(ResourceManager& rm);
		void LoadTextures(ResourceManager& rm);

		const std::string m_FilePath = "Sounds/";

	};

}

