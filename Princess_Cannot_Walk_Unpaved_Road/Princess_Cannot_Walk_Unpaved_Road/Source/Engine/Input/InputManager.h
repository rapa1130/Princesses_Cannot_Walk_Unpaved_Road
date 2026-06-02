#pragma once
#include <Windows.h>

namespace Bisang
{
    struct MousePos
    {
        int x, y;
    };

	class InputManager
	{
	public:
        void BeginFrame();

        void ProcessMessage(UINT msg, WPARAM wparam, LPARAM lparam);

        bool IsKeyDown(int key) const;
        bool IsKeyPressed(int key) const;
        bool IsKeyReleased(int key) const;

        bool IsMouseDown(int button) const;
        bool IsMousePressed(int button) const;
        bool IsMouseReleased(int button) const;

        const MousePos& GetMousePos() const;

    private:
        bool m_keyDown[256] = {};
        bool m_prevKeyDown[256] = {};

        bool m_mouseDown[3] = {};
        bool m_prevMouseDown[3] = {};

        MousePos m_mousePos = { 0, 0 };
	};
}