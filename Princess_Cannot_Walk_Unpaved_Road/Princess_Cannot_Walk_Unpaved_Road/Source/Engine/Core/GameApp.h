#pragma once
#include <memory>

namespace Bisang
{
    class Window;
    class SceneManager;
    class ResourceManager;
    class InputManager;

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
    };
}
