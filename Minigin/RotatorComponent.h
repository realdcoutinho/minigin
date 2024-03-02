#pragma once
#include "BaseComponent.h"
#include <glm/glm.hpp>
#include "TransformComponent.h"
#include <memory>

namespace dae {

    class RotatorComponent : public BaseComponent 
    {
    public:
        RotatorComponent(std::shared_ptr<GameObject> pOwner, float radius, float speed);
        RotatorComponent(GameObject* pOwner, float radius, float speed);
        void Update(float elapsed) override;
        virtual void Render() const override;

    private:
        TransformComponent* m_pTransform{};

        float m_Radius{};
        float m_RotSpeed{};
        float m_CurRadians{};
        glm::vec3 m_Center{};
       
    };

}

