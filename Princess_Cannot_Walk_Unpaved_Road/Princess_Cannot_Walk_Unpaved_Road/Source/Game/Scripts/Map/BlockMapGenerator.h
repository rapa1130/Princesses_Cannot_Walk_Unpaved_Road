#pragma once

#include "Engine/Components/Script.h"
#include "Engine/Math/Int3.h"

#include "Engine/Components/BlockMap/BlockObject.h"
#include "Game/Scripts/Blocks/BlockId.h"

namespace Bisang
{
    class BlockMap;

    class BlockMapGenerator : public Script
    {
    public:
        BlockMapGenerator(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;

        void Generate();
        void GenerateProceduralMap(unsigned int seed, int width, int height, int depth);

    private:
        void MakeStartZone(const Int3& startPosition, int radius);
        void MakeInitialRoad(Int3& startPos);

        unsigned int CreateRandomSeed() const;
        BlockObject MakeBlock(BlockId id) const;

    private:
        BlockMap* m_blockMap = nullptr;
        Int3 m_startPosition;
    };
}
