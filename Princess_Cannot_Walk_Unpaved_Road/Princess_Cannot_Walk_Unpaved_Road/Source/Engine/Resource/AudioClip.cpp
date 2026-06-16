#include "AudioClip.h"
#include <fstream>
#include <algorithm>

namespace Bisang
{
    static bool ReadFourCC(std::ifstream& file, char out[4])
    {
        file.read(out, 4);
        return file.good();
    }

    bool AudioClip::LoadFromFile(const std::wstring& path)
    {
        std::ifstream file(path, std::ios::binary);
        if (!file.is_open()) return false;

        char riff[4];
        char wave[4];
        uint32_t riffSize = 0;

        ReadFourCC(file, riff);
        file.read(reinterpret_cast<char*>(&riffSize), sizeof(riffSize));
        ReadFourCC(file, wave);

        if (strncmp(riff, "RIFF", 4) != 0 || strncmp(wave, "WAVE", 4) != 0)
            return false;

        bool hasFmt = false;
        bool hasData = false;

        while (file.good())
        {
            char chunkId[4];
            uint32_t chunkSize = 0;

            if (!ReadFourCC(file, chunkId)) break;
            file.read(reinterpret_cast<char*>(&chunkSize), sizeof(chunkSize));

            if (strncmp(chunkId, "fmt ", 4) == 0)
            {
                uint32_t readSize = (std::min)(chunkSize, static_cast<uint32_t>(sizeof(m_format)));
                file.read(reinterpret_cast<char*>(&m_format), readSize);

                if (chunkSize > readSize)
                    file.seekg(chunkSize - readSize, std::ios::cur);

                hasFmt = true;
            }
            else if (strncmp(chunkId, "data", 4) == 0)
            {
                m_data.resize(chunkSize);
                file.read(reinterpret_cast<char*>(m_data.data()), chunkSize);
                hasData = true;
            }
            else
            {
                file.seekg(chunkSize, std::ios::cur);
            }

            if (chunkSize % 2 == 1)
                file.seekg(1, std::ios::cur);
        }

        return hasFmt && hasData;
    }
}