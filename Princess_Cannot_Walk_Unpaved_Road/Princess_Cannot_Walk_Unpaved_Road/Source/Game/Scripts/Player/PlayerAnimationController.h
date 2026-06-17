#pragma once

#include "Engine/Components/Script.h"

#include <string>

#define PlayerAnimCount 16

namespace Bisang
{
    class InputManager;
    class Animator;
    class PlayerStatus;
    class PlayerController;

    class PlayerAnimationController : public Script
    {
    public:
        PlayerAnimationController(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;
        void Update(float dT) override;
        void SetPlayerNumber(int playerNum) { m_playerNumber = playerNum; }

    private:
        void InitializeAnimator();
        void UpdateAnimation();
        int m_playerNumber = 1;

    private:
        Animator* m_animator = nullptr;
        PlayerController* m_controller = nullptr;
        PlayerStatus* m_playerStatus = nullptr;

        std::wstring m_nameArr[PlayerAnimCount] =
        {
            L"FrontLeft",
            L"FrontRight",
            L"BackLeft",
            L"BackRight",
            L"Front",
            L"Back",
            L"Left",
            L"Right",
            L"RaiseHand_FrontLeft",
            L"RaiseHand_FrontRight",
            L"RaiseHand_BackLeft",
            L"RaiseHand_BackRight",
            L"RaiseHand_Front",
            L"RaiseHand_Back",
            L"RaiseHand_Left",
            L"RaiseHand_Right"
        };
    };
}