#include "InputManager.h"
#include <algorithm>
#include <windowsx.h>
#include "Engine/Core/Debug.h"

namespace Bisang
{
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
			m_mouseDown[static_cast<int>(MouseButton::Left)] = true;
			break;

		case WM_LBUTTONUP:
			m_mouseDown[static_cast<int>(MouseButton::Left)] = false;
			break;

		case WM_RBUTTONDOWN:
			m_mouseDown[static_cast<int>(MouseButton::Right)] = true;
			break;

		case WM_RBUTTONUP:
			m_mouseDown[static_cast<int>(MouseButton::Right)] = false;
			break;

		case WM_MBUTTONDOWN:
			m_mouseDown[static_cast<int>(MouseButton::Middle)] = true;
			break;

		case WM_MBUTTONUP:
			m_mouseDown[static_cast<int>(MouseButton::Middle)] = false;
			break;
		}
	}

	void InputManager::BeginFrame()
	{
		std::copy(std::begin(m_keyDown), std::end(m_keyDown), std::begin(m_prevKeyDown));
		std::copy(std::begin(m_mouseDown), std::end(m_mouseDown), std::begin(m_prevMouseDown));
	}

	bool InputManager::IsKeyDown(KeyCode key) const
	{
		return m_keyDown[static_cast<int>(key)];
	}

	bool InputManager::IsKeyPressed(KeyCode key) const
	{
		const int index = static_cast<int>(key);
		return m_keyDown[index] && !m_prevKeyDown[index];
	}

	bool InputManager::IsKeyReleased(KeyCode key) const
	{
		const int index = static_cast<int>(key);
		return !m_keyDown[index] && m_prevKeyDown[index];
	}

	bool InputManager::IsMouseDown(MouseButton button) const
	{
		return m_mouseDown[static_cast<int>(button)];
	}

	bool InputManager::IsMousePressed(MouseButton button) const
	{
		const int index = static_cast<int>(button);
		return m_mouseDown[index] && !m_prevMouseDown[index];
	}

	bool InputManager::IsMouseReleased(MouseButton button) const
	{
		const int index = static_cast<int>(button);
		return !m_mouseDown[index] && m_prevMouseDown[index];
	}

	const MousePos& InputManager::GetMousePos() const
	{
		return m_mousePos;
	}


}