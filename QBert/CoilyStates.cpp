#include "CoilyState.h"
#include "GameObject.h"
#include "TriangularGrid.h"
#include <iostream>
#include "CoilyComponent.h"
#include "GridNode.h"


namespace dae
{
    CoilyState::CoilyState(CoilyComponent* coily)
        : m_Coily(coily)
    {
    }

    std::unique_ptr<CoilyState> EggState::HandleInput(CoilyComponent* coily, GridNode& node)
    {
        if (node.GetNodeInfo().lastRow)
        {
			return std::make_unique<SnakeState>(coily);
		}
        return nullptr;
    }

    void EggState::Enter()
    {
        m_State = CoilyForm::Egg;
    }

    void EggState::Update()
    {

    }

    void EggState::Exit()
    {
        std::cout << "EggState Exit" << std::endl;
    }

    std::unique_ptr<CoilyState> SnakeState::HandleInput(CoilyComponent* coily, GridNode& node)
    {
        coily;
        node;
        return nullptr; // No further transitions in this example
    }

    void SnakeState::Enter()
    {
        if (m_Coily)
        {
            m_State = CoilyForm::Snake;
            std::cout << "Coily is now a snake" << std::endl;
            m_Coily->Evolve();
            //m_Coily->Hunt();

		}
    }

    void SnakeState::Update()
    {
    }

    void SnakeState::Exit()
    {
    }
}
