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
        // 인풋 매니저 윈도우 입력 감지 시작
        /*m_window->SetInputManager(m_inputManager.get());*/

        return true;
    }

    void GameApp::Run()
    {
        while (true)
        {
            // 메세지 펌핑
            MSG msg = {};
            while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE))
            {
                if (msg.message == WM_QUIT)
                    return;

                // 인풋 기록
                if (m_inputManager != nullptr)
                {
                    m_inputManager->ObserveInput(msg);
                  
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
