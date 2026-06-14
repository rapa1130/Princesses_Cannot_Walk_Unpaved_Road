#pragma once

#include "Engine/Components/Script.h"

#include <string>

#define PrincessAnimCount 4

namespace Bisang
{
    class InputManager;
    class Animator;
    class PlayerStatus;
    class PrincessController;

    class PrincessAnimationController : public Script
    {
    public:
        PrincessAnimationController(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;
        void Update(float dT) override;

    private:
        void InitializeAnimator();
        void UpdateAnimation();

    private:
        InputManager* m_input = nullptr;
        Animator* m_animator = nullptr;
        PrincessController* m_prinController = nullptr;

        std::wstring m_nameArr[PrincessAnimCount] =
        {
            L"Front",
            L"Back",
            L"Left",
            L"Right",
        };
    };
}