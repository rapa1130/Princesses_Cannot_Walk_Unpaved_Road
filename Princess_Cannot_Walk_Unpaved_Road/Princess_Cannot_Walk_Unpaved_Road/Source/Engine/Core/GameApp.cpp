#include "GameApp.h"
#include "Engine/Core/Debug.h"
#include "Engine/Windows/Window.h"

namespace Bisang
{
    GameApp::GameApp()
        : m_window(std::make_unique<Window>())
    {
    }

    GameApp::~GameApp() = default;

    bool GameApp::Initialize()
    {
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

        }
    }

    void GameApp::Finalize()
    {
    }
}
