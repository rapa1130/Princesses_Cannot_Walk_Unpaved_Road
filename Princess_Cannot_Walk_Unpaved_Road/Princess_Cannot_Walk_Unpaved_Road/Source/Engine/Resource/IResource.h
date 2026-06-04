#pragma once
#include <string>

namespace Bisang
{
    class IResource
    {
    public:
        virtual ~IResource() = default;

        //virtual bool LoadFromFile(const std::wstring& path) = 0;
    };
}