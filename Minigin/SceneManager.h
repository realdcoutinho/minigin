#pragma once
#include <vector>
#include <string>
#include <memory>
//#include "Scene.h"
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void FixedUpdate();

		void Render();

		void SetActiveScene(const std::string& name);
		void SetActiveScene(const Scene& scene);

		void SwitchScene(const std::string& name);
		void SwitchScene();

		Scene& GetActiveScene() const;
		Scene& GetSceneByName(const std::string& name) const;
		~SceneManager() override;

		void SetActiveTimer();

		void DestroyAllScenes();

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::vector<std::shared_ptr<Scene>> m_scenes;
		Scene* m_pActiveScene;
	};
}
