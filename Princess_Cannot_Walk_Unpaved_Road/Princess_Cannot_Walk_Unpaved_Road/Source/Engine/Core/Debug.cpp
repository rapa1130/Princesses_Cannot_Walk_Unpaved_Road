#include "Debug.h"

#include <iostream>

namespace Bisang
{
    void Debug::Log(const std::string& message)
    {
#ifdef _DEBUG
        std::cout << "[Log] " << message << std::endl;
#endif
    }

    void Debug::Warning(const std::string& message)
    {
#ifdef _DEBUG
        std::cout << "[Warning] " << message << std::endl;
#endif
    }

    void Debug::WarningWithLocation(const std::string& message, const char* file, int line)
    {
#ifdef _DEBUG
        std::cout << "[Warning] "
            << message
            << " (" << file << ":" << line << ")"
            << std::endl;
#endif
    }

    void Debug::Error(const std::string& message)
    {
#ifdef _DEBUG
        std::cerr << "[Error] " << message << std::endl;
#endif
    }

    void Debug::LogWithLocation(const std::string& message, const char* file, int line)
    {
#ifdef _DEBUG
        std::cout << "[Log] "
            << message
            << " (" << file << ":" << line << ")"
            << std::endl;
#endif
    }

    void Debug::ErrorWithLocation(const std::string& message, const char* file, int line)
    {
#ifdef _DEBUG
        std::cerr << "[Error] "
            << message
            << " (" << file << ":" << line << ")"
            << std::endl;
#endif
    }
}
