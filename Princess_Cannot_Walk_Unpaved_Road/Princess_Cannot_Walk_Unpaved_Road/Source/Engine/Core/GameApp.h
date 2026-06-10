#pragma once
#include <memory>

namespace Bisang
{
    class Window;
    class SceneManager;
    class ResourceManager;
    class InputManager;
    class Renderer;
    class GameTimer;
    class PrefabFactory;

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
        std::unique_ptr<InputManager> m_inputManager;
        std::unique_ptr<ResourceManager> m_resourceManager;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<PrefabFactory> m_prefabFactory;
        std::unique_ptr<SceneManager> m_sceneManager;


        std::unique_ptr<GameTimer> m_gameTimer;
        float m_deltaTime = 0.0f;
        float m_deltaTimeAccumulator = 0.0f;
        float m_fixedDeltaTime = 0.2f;
    private:
    };
}
