#pragma once

#include "Engine/Components/Component.h"
#include "Engine/Math/Vector.h"
#include <d2d1helper.h>

namespace Bisang
{
    class Transform;
    class Camera2D : public Component
    {
    public:
        Camera2D(GameObject* ownerObj);

        D2D1::Matrix3x2F GetViewMatrix() const;

        void SetCameraPostion(const Vector3& pos);
        void SetCameraRotation(float rot);
        void SetCameraScale(const Vector3& scale);


        Vector3 GetCameraPosition() const;
        float GetCameraRotation() const;
        Vector3 GetCameraScale() const;

    private:
        Transform* m_transform = nullptr;

    };
}