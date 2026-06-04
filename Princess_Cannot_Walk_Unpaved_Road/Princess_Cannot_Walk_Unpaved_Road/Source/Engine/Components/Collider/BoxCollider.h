#pragma once
#include "Engine/Components/Collider/Collider.h"

namespace Bisang
{
    class BoxCollider : public Collider
    {
    public:
        BoxCollider(GameObject* ownerObj, Scene* scene)
            : Collider(ownerObj, scene, ColliderType::Box)
        {
        }

        void SetSize(Vector2 size) { m_size = size; }
        Vector2 GetSize() const;

    private:
        Vector2 m_size = { 1.0f, 1.0f };
    };
}