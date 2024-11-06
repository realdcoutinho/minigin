#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
#include "TransformComponent.h"
#include <memory>

namespace dae {

    class RotatorComponent : public BaseComponent 
    {
    public:
        RotatorComponent(GameObject& pOwner, float radius, float speed);
        void Update() override;
        virtual void Render() override;

    private:
        TransformComponent* m_pTransform{};

        float m_Radius{};
        float m_RotSpeed{};
        float m_CurRadians{};
        glm::vec3 m_Center{};
       
    };

}

