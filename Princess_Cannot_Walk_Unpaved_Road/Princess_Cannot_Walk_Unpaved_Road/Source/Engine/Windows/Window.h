#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>

namespace Bisang
{
    /**
     * @brief Win32 윈도우를 생성하고 관리하는 클래스
     */
    class Window
    {
    public:
        Window() = default;
        virtual ~Window() = default;

        /**
         * @brief Win32 윈도우를 생성한다.
         *
         * @param[in] className 등록 및 생성에 사용할 윈도우 클래스 이름
         * @param[in] windowName 창 제목에 표시할 윈도우 이름
         * @param[in] width 생성할 클라이언트 영역 너비
         * @param[in] height 생성할 클라이언트 영역 높이
         *
         * @return 생성에 성공하면 true, 실패하면 false
         */
        bool Create(const wchar_t* className, const wchar_t* windowName, int width, int height);

        /**
         * @brief 생성된 Win32 윈도우를 파괴한다.
         */
        void Destroy();

        HWND GetHandle() const { return m_hWnd; }
        int GetWidth() const { return m_clientWidth; }
        int GetHeight() const { return m_clientHeight; }

    protected:
        /**
         * @brief Win32 윈도우 메시지를 처리한다.
         *
         * @param[in] hwnd 메시지를 받은 윈도우 핸들
         * @param[in] msg 처리할 윈도우 메시지
         * @param[in] wparam 메시지의 추가 데이터
         * @param[in] lparam 메시지의 추가 데이터
         *
         * @return 메시지 처리 결과
         */
        friend LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

        /**
         * @brief 윈도우 크기가 변경될 때 호출된다.
         *
         * @param[in] width 변경된 클라이언트 영역 너비
         * @param[in] height 변경된 클라이언트 영역 높이
         */
        virtual void OnResize(int width, int height);

        /**
         * @brief 사용자가 윈도우를 닫으려고 할 때 호출된다.
         */
        virtual void OnClose() {}

    private:
        HWND m_hWnd = nullptr;
        int m_clientWidth = 0;
        int m_clientHeight = 0;

        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        Window(Window&&) = delete;
        Window& operator=(Window&&) = delete;
    };
}
