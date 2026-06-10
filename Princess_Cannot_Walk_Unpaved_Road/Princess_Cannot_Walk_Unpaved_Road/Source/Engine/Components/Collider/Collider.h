#pragma once
#include "Engine/Components/Component.h"
#include "Engine/Math/Vector.h"
#include <functional>

namespace Bisang
{
    class Transform;

    enum class ColliderType
    {
        Box,
        Circle
    };

    class Collider : public Component
    {
    public:
        Collider(GameObject* ownerObj, ColliderType type);

        virtual ~Collider() = default;

        virtual void OnCollisionEnter(Collider* other) {}
        virtual void OnCollisionStay(Collider* other) {}
        virtual void OnCollisionExit(Collider* other) {}

        ColliderType GetType() const { return m_type; }

        void SetIsTrigger(bool isTrigger) { m_isTrigger = isTrigger; }
        bool GetIsTrigger() const { return m_isTrigger; }

        void SetOffset(Vector3 offset) { m_offset = offset; }
        Vector3 GetOffset() const { return m_offset; }

        Vector3 GetWorldPosition();

    protected:
        ColliderType m_type;
        Transform* m_transform = nullptr;

    private:
        Vector3 m_offset = { 0.0f, 0.0f, 0.0f };
        bool m_isTrigger = false;
    };
}