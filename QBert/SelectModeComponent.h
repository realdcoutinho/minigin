#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
#include <memory>


namespace dae
{
	class TextureComponent;
	class SelectModeStates;
	class SelectModeComponent final : public BaseComponent
	{
	public:
		SelectModeComponent(GameObject& pOwner);
		~SelectModeComponent();

		SelectModeComponent(const SelectModeComponent& other) = delete;
		SelectModeComponent(SelectModeComponent&& other) noexcept = delete;
		SelectModeComponent& operator=(const SelectModeComponent& other) = delete;
		SelectModeComponent& operator=(SelectModeComponent&& other) noexcept = delete;

		void Render() override;
		void Update() override;

		void HandleInput(glm::vec2 direction);
		void SelectMode();
	private:
		TextureComponent* m_pArrow;
		std::unique_ptr<SelectModeStates> m_pState;
	};

}

