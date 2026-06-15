#include "BlockMapGenerator.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"

#include "Game/Utility/PerlinNoise2D.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>


namespace Bisang
{
    void BlockMapGenerator::GenerateProceduralMap(
        BlockMap* blockMap,
        unsigned int seed,
        int width,
        int height,
        int depth,
        Int3 startPosition,
        Int3 endPosition
    )
    {
        if (blockMap == nullptr)
            return;

        if (width <= 0 || height <= 0 || depth <= 0)
            return;

        blockMap->InitMap(width, height, depth);

        const int groundZ = 0;
        const int objectZ = 1;

        const int octaveCount = 4;


        const float waterScale = 0.045f;
        const float treeScale = 0.090f;
        const float rockScale = 0.075f;
        const float clayScale = 0.065f;
        const float dirtScale = 0.065f;

        const float maxScale = (std::max)({
            waterScale,
            treeScale,
            rockScale,
            clayScale,
            dirtScale
            });

        int noiseGridWidth =
            static_cast<int>(std::ceil(width * maxScale * 8.0f)) + 4;

        int noiseGridDepth =
            static_cast<int>(std::ceil(depth * maxScale * 8.0f)) + 4;

        noiseGridWidth = (std::max)(noiseGridWidth, 8);
        noiseGridDepth = (std::max)(noiseGridDepth, 8);

        PerlinNoise2D waterNoise(noiseGridWidth, noiseGridDepth, seed + 100);
        PerlinNoise2D treeNoise(noiseGridWidth, noiseGridDepth, seed + 200);
        PerlinNoise2D rockNoise(noiseGridWidth, noiseGridDepth, seed + 300);
        PerlinNoise2D clayNoise(noiseGridWidth, noiseGridDepth, seed + 400);
        PerlinNoise2D dirtNoise(noiseGridWidth, noiseGridDepth, seed + 500);

        for (int y = 0; y < depth; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                float water = waterNoise.FractalNoise(
                    x * waterScale,
                    y * waterScale,
                    octaveCount);

                float tree = treeNoise.FractalNoise(
                    x * treeScale,
                    y * treeScale,
                    octaveCount);

                float rock = rockNoise.FractalNoise(
                    x * rockScale,
                    y * rockScale,
                    octaveCount);

                float clay = clayNoise.FractalNoise(
                    x * clayScale,
                    y * clayScale,
                    octaveCount);

                float dirt = dirtNoise.FractalNoise(
                    x * dirtScale,
                    y * dirtScale,
                    octaveCount);

                BlockId groundId = BlockId::Grass;

                if (water > 0.55f)
                {
                    groundId = BlockId::Water;
                }
                else if (dirt > 0.5f)
                {
                    groundId = BlockId::Dirt;
                }

                blockMap->SetBlock(
                    { x, y, groundZ },
                    static_cast<int>(groundId));

                if (groundId == BlockId::Water)
                    continue;

                if (rock > 0.6f)
                {
                    blockMap->SetBlock(
                        { x, y, objectZ },
                        static_cast<int>(BlockId::Rock));
                }
                else if (tree > 0.55f &&
                    (groundId == BlockId::Grass || groundId == BlockId::Dirt))
                {
                    BlockId treeId =
                        (std::rand() % 2 == 0)
                        ? BlockId::Tree
                        : BlockId::OrcTree;

                    blockMap->SetBlock(
                        { x, y, objectZ },
                        static_cast<int>(treeId));
                }
                else if (clay > 0.5f &&
                    (groundId == BlockId::Grass || groundId == BlockId::Dirt))
                {
                    blockMap->SetBlock(
                        { x, y, objectZ },
                        static_cast<int>(BlockId::Clay));
                }
            }
        }

        MakeEmptytZone(blockMap, startPosition, 7);
        MakeEmptytZone(blockMap, endPosition, 7);
        MakeInitialRoad(blockMap, startPosition);
    }


    void BlockMapGenerator::MakeEmptytZone(BlockMap* blockMap, const Int3& pos, int radius)
    {
        if (blockMap == nullptr)
            return;

        if (radius <= 0)
            return;

        int centerX = pos.x;
        int centerY = pos.y;

        int left = centerX - radius;
        int right = centerX + radius;
        int top = centerY + radius;
        int bottom = centerY - radius;

        int radiusSquared = radius * radius;

        for (int nowX = left; nowX < right; nowX++)
        {
            for (int nowY = bottom; nowY < top; nowY++)
            {
                int dx = nowX - centerX;
                int dy = nowY - centerY;

                if (dx * dx + dy * dy >= radiusSquared)
                    continue;

                Int3 objectPos{ nowX, nowY, pos.z };
                if (blockMap->InBounds(objectPos))
                {
                    blockMap->RemoveBlock(objectPos);
                }

                Int3 groundPos{ nowX, nowY, 0 };
                int zeroFloorBlock = blockMap->GetBlock(groundPos);
                if (zeroFloorBlock == static_cast<int>(BlockId::Water))
                {
                    blockMap->SetBlock(groundPos, static_cast<int>(BlockId::Grass));
                }
            }
        }

        blockMap->SetBlock(pos + Int3{1, 2, 0 }, static_cast<int>(BlockId::Axe));
        blockMap->SetBlock(pos + Int3{1, 1, 0}, static_cast<int>(BlockId::PickAxe));
        blockMap->SetBlock(pos + Int3{ 1, 3, 0 }, static_cast<int>(BlockId::Hammer));
        blockMap->SetBlock(pos + Int3{ 2, 2, 0 }, static_cast<int>(BlockId::ClayResource));
        blockMap->SetBlock(pos + Int3{ 2, 1, 0 }, static_cast<int>(BlockId::TreeResource));
    }

    void BlockMapGenerator::MakeInitialRoad(BlockMap* blockMap, Int3& startPos)
    {   
        for (int nowY = 0; nowY <= startPos.y; nowY++)
        {
            Int3 pos{ startPos.x,nowY,1 };
            Int3 underPos{ startPos.x,nowY,0 };
            
            if (blockMap->GetBlock(underPos) == static_cast<int>(BlockId::Water))
                blockMap->SetBlock(underPos, static_cast<int>(BlockId::Dirt));
            blockMap->SetBlock(pos, static_cast<int>(BlockId::RailPath));
        }

        blockMap->SetBlock({ startPos.x + 1,startPos.y,1 }, static_cast<int>(BlockId::RailPath));
        blockMap->SetBlock({ startPos.x + 2,startPos.y,1 }, static_cast<int>(BlockId::RailPath));
        blockMap->SetBlock({ startPos.x + 3,startPos.y,1 }, static_cast<int>(BlockId::RailPath));
        blockMap->SetBlock({ startPos.x + 3,startPos.y+1,1 }, static_cast<int>(BlockId::RailPath));
        blockMap->SetBlock({ startPos.x + 3,startPos.y+2,1 }, static_cast<int>(BlockId::RailPath));
    }
}
