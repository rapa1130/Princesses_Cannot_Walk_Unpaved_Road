#pragma once
#include "Engine/Math/Int3.h"

#include "Engine/Components/BlockMap/BlockObject.h"
#include "Game/Scripts/Blocks/BlockId.h"

namespace Bisang
{
    class BlockMap;

    class BlockMapGenerator
    {
    public:
        void GenerateProceduralMap(
            BlockMap* blockMap,
            unsigned int seed,
            int width,
            int height,
            int depth,
            Int3 startPosition,
            Int3 endPosition
        );


    private:
        void MakeEmptytZone(BlockMap* blockMap, const Int3& pos, int radius);
        void MakeInitialRoad(BlockMap* blockMap, Int3& startPos);
    };
}
