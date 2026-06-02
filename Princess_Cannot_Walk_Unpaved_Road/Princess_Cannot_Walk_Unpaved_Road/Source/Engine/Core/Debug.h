#pragma once
#include <string>

#ifdef _DEBUG

#define DEBUG_LOG(message) ::Bisang::Debug::Log(message)
#define DEBUG_WARNING(message) ::Bisang::Debug::Warning(message)
#define DEBUG_ERROR(message) ::Bisang::Debug::Error(message)

#define DEBUG_LOG_LOCATION(message) ::Bisang::Debug::LogWithLocation(message, __FILE__, __LINE__)
#define DEBUG_WARNING_LOCATION(message) ::Bisang::Debug::WarningWithLocation(message, __FILE__, __LINE__)
#define DEBUG_ERROR_LOCATION(message) ::Bisang::Debug::ErrorWithLocation(message, __FILE__, __LINE__)

#else

#define DEBUG_LOG(message)
#define DEBUG_WARNING(message)
#define DEBUG_ERROR(message)

#define DEBUG_LOG_LOCATION(message)
#define DEBUG_WARNING_LOCATION(message)
#define DEBUG_ERROR_LOCATION(message)

#endif

namespace Bisang
{
     /**
     * @brief 콘솔 디버그 출력을 담당하는 클래스
     *
     * @details
     * 로그, 경고, 에러 메시지를 콘솔에 출력한다.
     * 개발 중 디버깅 목적으로 사용하며, 빌드 설정에 따라 비활성화할 수 있다.
     */
    class Debug
    {
    public:
        /**
         * @brief 일반 로그 메시지를 출력한다.
         *
         * @param[in] message 출력할 로그 메시지
         */
        static void Log(const std::string& message);

        /**
         * @brief 경고 메시지를 출력한다.
         *
         * @param[in] message 출력할 경고 메시지
         */
        static void Warning(const std::string& message);

        /**
         * @brief 파일명과 라인 번호를 포함한 경고 메시지를 출력한다.
         *
         * @param[in] message 출력할 경고 메시지
         * @param[in] file 경고가 발생한 파일명
         * @param[in] line 경고가 발생한 라인 번호
         */
        static void WarningWithLocation(const std::string& message, const char* file, int line);

        /**
         * @brief 에러 메시지를 출력한다.
         *
         * @param[in] message 출력할 에러 메시지
         */
        static void Error(const std::string& message);

        /**
         * @brief 파일명과 라인 번호를 포함한 로그를 출력한다.
         *
         * @param[in] message 출력할 메시지
         * @param[in] file 로그가 발생한 파일명
         * @param[in] line 로그가 발생한 라인 번호
         */
        static void LogWithLocation(const std::string& message, const char* file, int line);

        /**
         * @brief 파일명과 라인 번호를 포함한 에러 로그를 출력한다.
         *
         * @param[in] message 출력할 에러 메시지
         * @param[in] file 에러가 발생한 파일명
         * @param[in] line 에러가 발생한 라인 번호
         */
        static void ErrorWithLocation(const std::string& message, const char* file, int line);

    private:
        Debug() = delete;
        ~Debug() = delete;
    };
}
