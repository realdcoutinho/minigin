#pragma once
#include "BaseComponent.h"
#include <string>
#include <vector>


namespace dae
{
	class CharacterComponent;
	class TricklePathComponent;
	class PathFinderComponent;
	class TriangularGrid;
	class GridNode;
	class CoilyState;
	struct NodeInfo;

	class CoilyComponent final : public BaseComponent
	{
	public:
		CoilyComponent(GameObject& pOwner, TriangularGrid& grid, bool playableChar = false);
		~CoilyComponent();

		CoilyComponent(const CoilyComponent& other) = delete;
		CoilyComponent(CoilyComponent&& other) noexcept = delete;
		CoilyComponent& operator=(const CoilyComponent& other) = delete;
		CoilyComponent& operator=(CoilyComponent&& other) noexcept = delete;

		void Render() override;
		void Update() override;

		void HandleInput(GridNode& node);
		void Evolve();

		void Hunt(GridNode& bertNode);
		void Hunt(std::vector<GameObject*> qberts);

		GameObject* GetTargetQbert() const { return m_TargetQbert; }
		int GetPoints() const { return m_Points; }



	private:
		bool m_IsPlayableChar{ false };
		int m_Points{ 500 };
		CharacterComponent* m_Character;
		TricklePathComponent* m_TricklePath;
		PathFinderComponent* m_PathFinder;
		std::unique_ptr<CoilyState> m_pCoilyState;
		const std::string m_CoilyTextureFile{ "Coily Spritesheet.png" };
		const std::string m_EggTextureFile{"Egg.png"};
		GameObject* m_TargetQbert;


	};
}



