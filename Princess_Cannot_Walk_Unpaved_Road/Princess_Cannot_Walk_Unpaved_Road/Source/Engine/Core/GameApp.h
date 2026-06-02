#pragma once
#include <memory>

namespace Bisang
{
    class Window;

    class GameApp
    {
    public:
        GameApp();
        ~GameApp();

        bool Initialize();
        void Run();
        void Finalize();

    private:
        std::unique_ptr<Window> m_window;
    };
}
