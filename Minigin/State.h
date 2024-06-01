#pragma once
// State.h

namespace dae
{
    class IState
    {
    public:
        virtual ~IState() {}  // Virtual destructor to ensure proper cleanup of derived classes

        // Define pure virtual methods that must be implemented by any derived state classes
        virtual void Enter() = 0;  // Called when entering the state
        virtual void Update() = 0;  // Called to update the state
        //virtual void render() = 0;  // Called to render the state
        virtual void Exit() = 0;  // Called when exiting the state
    };
}