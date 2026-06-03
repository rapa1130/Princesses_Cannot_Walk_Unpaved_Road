#include "GameApp.h"
#include "Engine/Core/Debug.h"
#include "Engine/Windows/Window.h"
#include "Engine/Input/InputManager.h"

#include <iostream>

namespace Bisang
{
    GameApp::GameApp()
        : m_window(std::make_unique<Window>()),
          m_inputManager(std::make_unique<InputManager>())
    {
    }

    GameApp::~GameApp() = default;

    bool GameApp::Initialize()
    {
        // 윈도우 생성
        if (false == (m_window->Create(L"GameApp", L"Princess_Cannot_Walk_Unpaved_Road", 1000, 1000)))
        {
            return false;
        }

        return true;
    }

    void GameApp::Run()
    {
        while (true)
        {
            // 인풋 프레임 시작 처리
            m_inputManager->BeginFrame();

            // 메세지 펌핑
            MSG msg = {};
            while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                    return;

                // 인풋 기록
                if (m_inputManager != nullptr)
                {
                    m_inputManager->ProcessMessage(msg);
                }

                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }

        }
    }

    void GameApp::Finalize()
    {
    }
}
