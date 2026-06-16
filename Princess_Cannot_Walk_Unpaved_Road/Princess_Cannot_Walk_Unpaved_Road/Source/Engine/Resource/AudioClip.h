#pragma once
#include "Engine/Resource/IResource.h"
#include <xaudio2.h>
#include <vector>
#include <string>

namespace Bisang
{
    class AudioClip : public IResource
    {
    public:
        bool LoadFromFile(const std::wstring& path);

        const WAVEFORMATEX* GetFormat() const
        {
            return reinterpret_cast<const WAVEFORMATEX*>(&m_format);
        }

        const BYTE* GetData() const { return m_data.data(); }
        UINT32 GetDataSize() const { return static_cast<UINT32>(m_data.size()); }

    private:
        WAVEFORMATEXTENSIBLE m_format = {};
        std::vector<BYTE> m_data;
    };
}