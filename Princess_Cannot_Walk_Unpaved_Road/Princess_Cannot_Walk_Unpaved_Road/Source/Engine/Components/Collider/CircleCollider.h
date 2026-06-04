#pragma once
#include "Engine/Components/Collider/Collider.h"

namespace Bisang
{
    class CircleCollider : public Collider
    {
    public:
        CircleCollider(GameObject* ownerObj, Scene* scene)
            : Collider(ownerObj, scene, ColliderType::Circle)
        {
        }

        void SetRadius(float radius) { m_radius = radius; }
        float GetRadius() const;

    private:
        float m_radius = 0.5f;
    };
}