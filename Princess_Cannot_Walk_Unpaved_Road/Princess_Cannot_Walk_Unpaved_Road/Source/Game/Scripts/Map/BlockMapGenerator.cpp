#include "BlockMapGenerator.h"

#include "Engine/Object/GameObject.h"

#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/BlockMap/BlockMapRenderer.h"

#include "Game/Scripts/Blocks/BlockInfoProvider.h"
#include "Game/Utility/PerlinNoise2D.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <random>

namespace Bisang
{
    void BlockMapGenerator::Start()
    {
        m_blockMap = m_ownerObj->GetComponent<BlockMap>();
        GenerateProceduralMap(
            CreateRandomSeed(),
            30,
            3,
            90
        );

        BlockMapRenderer* blockMapRenderer = m_ownerObj->GetComponent<BlockMapRenderer>();
        BlockObjectInfoProvider* blockMapInfoProvider = m_ownerObj->GetComponent<BlockObjectInfoProvider>();
        blockMapRenderer->SetBlockObjectInfoTable(blockMapInfoProvider->GetTable());
    }

    void BlockMapGenerator::Generate()
    {
        if (m_blockMap == nullptr)
            return;

        m_blockMap->InitMap(30, 3, 90);

        for (int x = 0; x < 10; ++x)
        {
            for (int y = 0; y < 10; ++y)
            {
                m_blockMap->SetBlock({ x, y, 0 }, static_cast<int>(BlockId::Grass));
            }
        }
    }

    void BlockMapGenerator::GenerateProceduralMap(
        unsigned int seed,
        int width,
        int height,
        int depth)
    {
        if (m_blockMap == nullptr)
            return;

        if (width <= 0 || height <= 0 || depth <= 0)
            return;

        m_blockMap->InitMap(width, height, depth);

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

                m_blockMap->SetBlock(
                    { x, y, groundZ },
                    static_cast<int>(groundId));

                if (groundId == BlockId::Water)
                    continue;

                if (rock > 0.6f)
                {
                    m_blockMap->SetBlock(
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

                    m_blockMap->SetBlock(
                        { x, y, objectZ },
                        static_cast<int>(treeId));
                }
                else if (clay > 0.5f &&
                    (groundId == BlockId::Grass || groundId == BlockId::Dirt))
                {
                    m_blockMap->SetBlock(
                        { x, y, objectZ },
                        static_cast<int>(BlockId::Clay));
                }
            }
        }
        Int3 startPos = { width / 2, 10, objectZ };
        MakeStartZone(startPos, 7);
        MakeInitialRoad(startPos);
    }

    void BlockMapGenerator::MakeStartZone(const Int3& startPosition, int radius)
    {
        if (m_blockMap == nullptr)
            return;

        if (radius <= 0)
            return;

        int centerX = startPosition.x;
        int centerY = startPosition.y;

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

                Int3 objectPos{ nowX, nowY, startPosition.z };
                if (m_blockMap->InBounds(objectPos))
                {
                    m_blockMap->RemoveBlock(objectPos);
                }

                Int3 groundPos{ nowX, nowY, 0 };
                int zeroFloorBlock = m_blockMap->GetBlock(groundPos);
                if (zeroFloorBlock == static_cast<int>(BlockId::Water))
                {
                    m_blockMap->SetBlock(groundPos, static_cast<int>(BlockId::Grass));
                }
            }
        }

        m_blockMap->SetBlock(startPosition, static_cast<int>(BlockId::Axe));
        m_blockMap->SetBlock(startPosition + Int3{1, 1, 0}, static_cast<int>(BlockId::PickAxe));
    }

    void BlockMapGenerator::MakeInitialRoad(Int3& startPos)
    {
        for (int nowY = 0; nowY <= startPos.y; nowY++)
        {
            Int3 pos{ startPos.x,nowY,1 };
            Int3 underPos{ startPos.x,nowY,0 };
            
            if (m_blockMap->GetBlock(underPos)->id == static_cast<int>(BlockId::Water))
                m_blockMap->SetBlock(underPos, MakeBlock(BlockId::Dirt));
            m_blockMap->SetBlock(pos, MakeBlock(BlockId::RailPath));
        }
    }

    BlockObject BlockMapGenerator::MakeBlock(BlockId id) const
    {
        BlockObject block;
        block.id = static_cast<int>(id);
        return block;
    }

    unsigned int BlockMapGenerator::CreateRandomSeed() const
    {
        std::random_device rd;
        return rd();
    }
}
