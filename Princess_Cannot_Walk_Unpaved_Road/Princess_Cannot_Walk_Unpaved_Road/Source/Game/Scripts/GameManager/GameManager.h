#pragma once

#include "Engine/Components/Script.h"
#include "Engine/Math/Int3.h"

namespace Bisang
{
    class BlockMap;

    class GameManager : public Script
    {
    public:
        GameManager(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;
        void Update(float dT) override;

        Int3 GetStartRailPosition() { return Int3(m_startPosition.x, 0, m_playerZ); }

    private:
        unsigned int CreateRandomSeed() const;
        void GenerateMap();

    private:
        BlockMap* m_blockMap = nullptr;
        int m_playerZ = 1;
        Int3 m_startPosition;
        Int3 m_endPosition;
    };
}