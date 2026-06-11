#include "GameApp.h"
#include "Engine/Core/Debug.h"
#include "Engine/Core/GameTimer.h"
#include "Engine/Windows/Window.h"
#include "Engine/Input/InputManager.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Renderer/Renderer.h"
#include "Engine/Scene/SceneManager.h"
#include "Engine/Prefab/PrefabFactory.h"

#include "Game/Scenes/SampleScene.h"
#include "Game/Scenes/BlockMapTestScene.h"
#include "Game/Prefabs/PlayerPrefab.h"
#include "Game/Prefabs/BlockMapPrefab.h"

#include <iostream>

namespace Bisang
{
    GameApp::GameApp()
    {
        m_window = std::make_unique<Window>();
        m_gameTimer = std::make_unique<GameTimer>();
        m_renderer = std::make_unique<Renderer>();
        
        m_resourceManager = std::make_unique<ResourceManager>();
        m_inputManager = std::make_unique<InputManager>();
        m_prefabFactory = std::make_unique<PrefabFactory>(m_resourceManager.get());
        m_context.resourceManager = m_resourceManager.get();
        m_context.inputManager = m_inputManager.get();
        m_context.prefabFactory = m_prefabFactory.get();

        m_sceneManager = std::make_unique<SceneManager>(&m_context, m_renderer.get());
    }

    GameApp::~GameApp() = default;

    bool GameApp::Initialize()
    {
        // 윈도우 생성
        if (false == (m_window->Create(L"GameApp", L"Princess_Cannot_Walk_Unpaved_Road", 1000, 1000)))
        {
            return false;
        }

        //리소스 매니저 초기화


        // 렌더러 초기화
        if (false == m_renderer->Initialize(
            m_window->GetHandle(),
            m_window->GetWidth(), 
            m_window->GetHeight())
            )
        {
            return false;
        }

        if (false == m_resourceManager->Initialize(m_renderer->GetD2DContext()))
        {
            return false;
        }

        // 씬 매니저 설정
        m_sceneManager->AddScene<SampleScene>("SampleScene");
        m_sceneManager->AddScene<BlockMapTestScene>("BlockMapTestScene");
        m_sceneManager->SetStartScene("BlockMapTestScene");

        // 프리팹 팩토리 설정
        m_prefabFactory->RegisterPrefab<PlayerPrefab>("Player");
        m_prefabFactory->RegisterPrefab<BlockMapPrefab>("BlockMap");

        // 타이머 초기화 ( 초기화 마지막 단계에 두는 것이 좋음 )
        m_gameTimer->Reset();

        return true;
    }

    void GameApp::Run()
    {
        m_sceneManager->InitCurrentScene();

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

            Update();
            Render();
        }
    }

    void GameApp::Finalize()
    {

    }

    void GameApp::Update()
    {
        // 델타 타임 계산 및 저장
        m_gameTimer->Tick();
        m_deltaTime = m_gameTimer->DeltaTime();

        // 가변 프레임 로직
        m_sceneManager->Update(m_deltaTime);

        // 고정 프레임 로직
        m_deltaTimeAccumulator += m_deltaTime;
        while (m_deltaTimeAccumulator >= m_fixedDeltaTime)
        {
            m_sceneManager->FixedUpdate();
            m_deltaTimeAccumulator -= m_fixedDeltaTime;
        }
    }

    void GameApp::Render()
    {
        Scene* currentScene = m_sceneManager->GetCureentScene();
        m_renderer->RenderScene(currentScene);
    }
}
