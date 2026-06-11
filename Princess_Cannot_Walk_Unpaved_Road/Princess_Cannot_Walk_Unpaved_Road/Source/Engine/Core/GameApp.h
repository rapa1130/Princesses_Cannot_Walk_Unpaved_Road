#pragma once
#include <memory>
#include "Engine/Core//GameContext.h"

namespace Bisang
{
    class Window;
    class GameTimer;
    class SceneManager;
    class Renderer;

    class GameApp
    {
    public:
        GameApp();
        ~GameApp();

        bool Initialize();
        void Run();
        void Finalize();

        void Update();
        void Render();

    private:
        std::unique_ptr<Window> m_window;
        std::unique_ptr<GameTimer> m_gameTimer;
        std::unique_ptr<SceneManager> m_sceneManager;
        std::unique_ptr<Renderer> m_renderer;

        std::unique_ptr<InputManager> m_inputManager;
        std::unique_ptr<ResourceManager> m_resourceManager;
        std::unique_ptr<PrefabFactory> m_prefabFactory;
        GameContext m_context;

        float m_deltaTime = 0.0f;
        float m_deltaTimeAccumulator = 0.0f;
        float m_fixedDeltaTime = 0.2f;
    private:
    };
}
