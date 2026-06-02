#include "Window.h"
#include "Engine/Input/InputManager.h"

namespace Bisang
{
    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
    {
        Window* window = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));

        // 윈도우 첫 생성시 받는 메세지
        if (msg == WM_NCCREATE)
        {
            CREATESTRUCTW* createStruct = reinterpret_cast<CREATESTRUCTW*>(lparam);
            window = static_cast<Window*>(createStruct->lpCreateParams);

            SetWindowLongPtrW(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
            window->m_hWnd = hwnd;
        }

        if (window != nullptr)
        {
            switch (msg)
            {
            // 윈도우 창 조절 시
            case WM_SIZE:
                window->OnResize(LOWORD(lparam), HIWORD(lparam));
                return 0;

            // 사용자가 창을 닫으려고 할 때
            case WM_CLOSE:
                window->OnClose();
                window->Destroy();
                return 0;

            // 윈도우 파괴 메세지
            case WM_NCDESTROY:
                window->m_hWnd = nullptr;
                SetWindowLongPtrW(hwnd, GWLP_USERDATA, 0);
                break;
            }
        }

        if (window->m_inputManager != nullptr)
        {
            window->m_inputManager->ProcessMessage(msg, wparam, lparam);
        }

        return DefWindowProcW(hwnd, msg, wparam, lparam);
    }

    bool Window::Create(const wchar_t* className, const wchar_t* windowName, int width, int height)
    {
        // 이미 생성된 윈도우가 있으면 실패
        if (m_hWnd != nullptr)
        {
            return false;
        }

        // 현재 실행 파일(EXE)의 인스턴스 핸들 획득
        HINSTANCE instance = GetModuleHandleW(nullptr);

        // 윈도우 클래스 정보 설정
        WNDCLASSEXW windowClass = {};
        windowClass.cbSize = sizeof(WNDCLASSEXW);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WndProc;
        windowClass.hInstance = instance;
        windowClass.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
        windowClass.lpszClassName = className;

        // 윈도우 클래스 등록
        if (RegisterClassExW(&windowClass) == 0)
        {
            DWORD error = GetLastError();

            // 이미 등록된 클래스가 아니라면 실패
            if (error != ERROR_CLASS_ALREADY_EXISTS)
            {
                return false;
            }
        }

        DWORD style = WS_OVERLAPPEDWINDOW;

        // 클라이언트 영역이 width x height가 되도록 전체 창 크기 계산
        RECT rect = { 0, 0, width, height };
        if (AdjustWindowRect(&rect, style, FALSE) == FALSE)
        {
            return false;
        }

        // 실제 윈도우 생성
        HWND hwnd = CreateWindowExW(
            0,
            className,
            windowName,
            style,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rect.right - rect.left,
            rect.bottom - rect.top,
            nullptr,
            nullptr,
            instance,
            this);     // 사용자 데이터로 this 전달

        if (hwnd == nullptr)
        {
            return false;
        }

        // 생성된 윈도우 정보 저장
        m_hWnd = hwnd;

        // 클라이언트 창 사이즈 저장 
        RECT rcClient = {};
        GetClientRect(m_hWnd, &rcClient);
         m_clientWidth = rcClient.right - rcClient.left;
         m_clientHeight = rcClient.bottom - rcClient.top;

        // 윈도우 표시 및 갱신
        ShowWindow(m_hWnd, SW_SHOW);
        UpdateWindow(m_hWnd);

        return true;
    }

    void Window::Destroy()
    {
        if (m_hWnd != nullptr)
        {
            DestroyWindow(m_hWnd);
            m_hWnd = nullptr;
        }
    }

    void Window::OnResize(int width, int height)
    {
        m_clientWidth = width;
        m_clientHeight = height;
    }

    void Window::SetInputManager(InputManager* inputManager)
    {
        if (inputManager == nullptr) return;
        m_inputManager = inputManager;
    }
}
