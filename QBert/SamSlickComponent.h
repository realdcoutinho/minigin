#pragma once
#include "BaseComponent.h"
#include <string>




namespace dae
{
	class CharacterComponent;
	class TricklePathComponent;
	class TriangularGrid;
	class SamSlickComponent final : public BaseComponent
	{
	public:
		SamSlickComponent(GameObject& pOwner, TriangularGrid& grid);
		~SamSlickComponent();

		SamSlickComponent(const SamSlickComponent& other) = delete;
		SamSlickComponent(SamSlickComponent&& other) noexcept = delete;
		SamSlickComponent& operator=(const SamSlickComponent& other) = delete;
		SamSlickComponent& operator=(SamSlickComponent&& other) noexcept = delete;

		void Render() override;
		void Update() override;

	private:
		CharacterComponent* m_Character;
		TricklePathComponent* m_TricklePath;

		const std::string m_SamTextureFile{ "SamSprite.png" };
		const std::string m_SlickTextureFile{ "SlickSprite.png" };
	};


}
