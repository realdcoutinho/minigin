#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class TriangularGrid;
	class CharacterComponent;
	class TricklePathComponent;
	class UggWrongwayComponent final : public BaseComponent
	{
	public:
		UggWrongwayComponent(GameObject& pOwner, TriangularGrid& grid);
		~UggWrongwayComponent();
		UggWrongwayComponent(const UggWrongwayComponent& other) = delete;
		UggWrongwayComponent(UggWrongwayComponent&& other) noexcept = delete;
		UggWrongwayComponent& operator=(const UggWrongwayComponent& other) = delete;
		UggWrongwayComponent& operator=(UggWrongwayComponent&& other) noexcept = delete;
		void Render() override;
		void Update() override;
	private:
		CharacterComponent* m_Character;
		TricklePathComponent* m_TricklePath;

		const std::string m_UggTexture{ "Ugg.png" };
		const std::string m_WrongwayTexture{ "Wrongway.png" };
	};
}


