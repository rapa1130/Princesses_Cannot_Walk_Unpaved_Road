#pragma once

#include "Engine/Components/Script.h"
#include "Engine/Math/Int3.h"
#include "Engine/Math/Vector.h"

namespace Bisang
{
    class Camera2D;
    
    class CameraController : public Script
    {
    public:
        CameraController(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;
        void Update(float dT) override;
        
        void CameraShake(float shakePower);

    private:
        Camera2D* m_cam2D = nullptr;
        Transform* m_princessTransform = nullptr;

        Vector3 m_initailPrincessPos;

        float m_shakeTimer = 0.0f;
        float m_shakeDuration = 0.35f;
        float m_shakePower = 18.0f;

        bool m_isShaking = false;
    };
}
