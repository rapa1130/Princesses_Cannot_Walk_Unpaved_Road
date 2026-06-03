#pragma once
#include <Windows.h>
#include "Engine/input/InputCode.h"

namespace Bisang
{
    /**
     * @brief 마우스 커서 위치를 저장하는 구조체
     */
    struct MousePos
    {
        int x, y;
    };

    /**
     * @brief 키보드 및 마우스 입력 상태를 관리하는 클래스
     *
     * Win32 메시지를 기반으로 입력 상태를 갱신하며,
     * 키 및 마우스 버튼의 Pressed / Down  / Released 상태를 제공한다.
     */
    class InputManager
    {
    public:
        /**
         * @brief 새로운 프레임 시작 시 이전 입력 상태를 저장한다.
         *
         * Pressed 및 Released 판정을 위해 현재 입력 상태를
         * 이전 상태 버퍼에 복사한다.
         */
        void BeginFrame();

        /**
         * @brief Win32 입력 메시지를 처리한다.
         *
         * 키보드 및 마우스 관련 메시지를 해석하여
         * 내부 입력 상태를 갱신한다.
         *
         * @param[in] msg 처리할 Win32 메시지
         */
        void ProcessMessage(const MSG& msg);

        /**
         * @brief 지정한 키가 현재 눌려있는지 확인한다.
         *
         * @param[in] key 가상 키 코드(Virtual Key Code)
         *
         * @return 키가 눌려있으면 true, 아니면 false
         */
        bool IsKeyDown(KeyCode key) const;

        /**
         * @brief 지정한 키가 이번 프레임에 눌렸는지 확인한다.
         *
         * @param[in] key 가상 키 코드(Virtual Key Code)
         *
         * @return 이번 프레임에 눌렸으면 true, 아니면 false
         */
        bool IsKeyPressed(KeyCode key) const;

        /**
         * @brief 지정한 키가 이번 프레임에 떼어졌는지 확인한다.
         *
         * @param[in] key 가상 키 코드(Virtual Key Code)
         *
         * @return 이번 프레임에 떼어졌으면 true, 아니면 false
         */
        bool IsKeyReleased(KeyCode key) const;

        /**
         * @brief 지정한 마우스 버튼이 현재 눌려있는지 확인한다.
         *
         * @param[in] button 마우스 버튼 인덱스
         *
         * @return 버튼이 눌려있으면 true, 아니면 false
         */
        bool IsMouseDown(MouseButton button) const;

        /**
         * @brief 지정한 마우스 버튼이 이번 프레임에 눌렸는지 확인한다.
         *
         * @param[in] button 마우스 버튼 인덱스
         *
         * @return 이번 프레임에 눌렸으면 true, 아니면 false
         */
        bool IsMousePressed(MouseButton button) const;

        /**
         * @brief 지정한 마우스 버튼이 이번 프레임에 떼어졌는지 확인한다.
         *
         * @param[in] button 마우스 버튼 인덱스
         *
         * @return 이번 프레임에 떼어졌으면 true, 아니면 false
         */
        
        bool IsMouseReleased(MouseButton button) const;

        /**
         * @brief 현재 마우스 커서 위치를 반환한다.
         *
         * @return 현재 마우스 위치 정보
         */
        const MousePos& GetMousePos() const;

        

    private:
        /// 현재 키 입력 상태
        bool m_keyDown[256] = {};

        /// 이전 프레임의 키 입력 상태
        bool m_prevKeyDown[256] = {};

        /// 현재 마우스 버튼 상태
        bool m_mouseDown[3] = {};

        /// 이전 프레임의 마우스 버튼 상태
        bool m_prevMouseDown[3] = {};

        /// 현재 마우스 위치
        MousePos m_mousePos = { 0, 0 };
    };
}