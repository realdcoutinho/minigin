#pragma once
#include <memory>
#include "State.h"

namespace dae
{
    enum class CoilyForm
    {
        Egg,
        Snake
    };

    class CoilyComponent;
    class GridNode;
    class CoilyState : public IState
    {
    public:
        CoilyState() = default;
        CoilyState(CoilyComponent* coily);
        virtual ~CoilyState() = default;

        virtual std::unique_ptr<CoilyState> HandleInput(CoilyComponent* coily, GridNode& node) = 0;
        virtual void Enter() override = 0;
        virtual void Update() override = 0;
        virtual void Exit() override = 0;

        CoilyForm GetState() { return m_State; };

    protected:
        CoilyComponent* m_Coily;
        CoilyForm m_State;
    };

    class EggState final : public CoilyState
    {
    public:
        EggState() = default;
        EggState(CoilyComponent* coily)
            : CoilyState(coily)
        {
        }
        virtual ~EggState() = default;

        virtual std::unique_ptr<CoilyState> HandleInput(CoilyComponent* coily, GridNode& node) override;
        virtual void Enter() override;
        virtual void Update() override;
        virtual void Exit() override;
    };

    class SnakeState final : public CoilyState
    {
    public:
        SnakeState() = default;
        SnakeState(CoilyComponent* coily)
            : CoilyState(coily)
        {
        }
        virtual ~SnakeState() = default;

        virtual std::unique_ptr<CoilyState> HandleInput(CoilyComponent* coily, GridNode& node) override;
        virtual void Enter() override;
        virtual void Update() override;
        virtual void Exit() override;
    };
}
