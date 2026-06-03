#include "InputManager.h"
#include <algorithm>
#include <windowsx.h>
#include "Engine/Core/Debug.h"

namespace Bisang
{
	void InputManager::ObserveInput(const MSG& msg)
	{
		BeginFrame();
		ProcessMessage(msg);
	}

	void InputManager::ProcessMessage(const MSG& msg)
	{
		LPARAM lparam = msg.lParam;
		WPARAM wparam = msg.wParam;

		switch (msg.message)
		{
		case WM_KEYDOWN:
			m_keyDown[wparam] = true;
			break;

		case WM_KEYUP:
			m_keyDown[wparam] = false;
			break;

		case WM_MOUSEMOVE:
			m_mousePos = { GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam) };
			break;

		case WM_LBUTTONDOWN:
			m_mouseDown[0] = true;
			break;

		case WM_LBUTTONUP:
			m_mouseDown[0] = false;
			break;

		case WM_RBUTTONDOWN:
			m_mouseDown[1] = true;
			break;

		case WM_RBUTTONUP:
			m_mouseDown[1] = false;
			break;

		case WM_MBUTTONDOWN:
			m_mouseDown[2] = true;
			break;

		case WM_MBUTTONUP:
			m_mouseDown[2] = false;
			break;
		}
	}

	void InputManager::BeginFrame()
	{
		std::copy(std::begin(m_keyDown), std::end(m_keyDown), std::begin(m_prevKeyDown));
		std::copy(std::begin(m_mouseDown), std::end(m_mouseDown), std::begin(m_prevMouseDown));
	}

	bool InputManager::IsKeyDown(int key) const
	{
		return m_keyDown[key];
	}

	bool InputManager::IsKeyPressed(int key) const
	{
		return m_keyDown[key] && !m_prevKeyDown[key];
	}

	bool InputManager::IsKeyReleased(int key) const
	{
		return !m_keyDown[key] && m_prevKeyDown[key];
	}

	bool InputManager::IsMouseDown(int button) const
	{
		return m_mouseDown[button];
	}

	bool InputManager::IsMousePressed(int button) const
	{
		return m_mouseDown[button] && !m_prevMouseDown[button];
	}

	bool InputManager::IsMouseReleased(int button) const
	{
		return !m_mouseDown[button] && m_prevMouseDown[button];
	}

	const MousePos& InputManager::GetMousePos() const
	{
		return m_mousePos;
	}


}