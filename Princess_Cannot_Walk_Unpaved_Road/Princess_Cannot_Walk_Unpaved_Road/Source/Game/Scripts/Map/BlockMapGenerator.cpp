#include "BlockMapGenerator.h"

#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Resource/ResourceManager.h"

#include "Game/Scripts/Blocks/BlockId.h"
#include "Game/Utility/PerlinNoise2D.h"

#include <algorithm>

namespace Bisang
{
	void BlockMapGenerator::Generate(BlockMap* blockMap)
	{
		blockMap->InitMap(30, 3, 90);

		for (int i = 0; i < 10; i++)
		{
			for (int ii = 0; ii < 10; ii++)
			{
				for (int iii = 0; iii <= 0; iii++)
				{
					Block* block = new Block(1, true, GetResourceManager()->LoadTexture(L"Assets/Textures/GrassBlock.png"));
					blockMap->SetBlock({ i, ii, iii }, block);
				}
			}
		}
	}

    void BlockMapGenerator::GenerateProceduralMap(unsigned int seed, int width, int height, int depth )
{
    if (width <= 0 || height <= 0 || depth <= 0)
        return;


    const int groundZ = 0;
    const int octaveCount = 4;
    const float waterScale = 0.045f;
    const float treeScale = 0.090f;
    const float rockScale = 0.075f;
    const float clayScale = 0.065f;
    const float dirtScale = 0.065f;

    const float maxScale = (std::max)({ waterScale, treeScale, rockScale, clayScale,dirtScale });

    // FractalNoise에서 frequency가 1,2,4,8로 올라가므로 grid 크기를 넉넉히 잡음
    int noiseGridWidth = static_cast<int>(std::ceil(width * maxScale * 8.0f)) + 4;
    int noiseGridDepth = static_cast<int>(std::ceil(depth * maxScale * 8.0f)) + 4;

    noiseGridWidth = (std::max)(noiseGridWidth, 8);
    noiseGridDepth = (std::max)(noiseGridDepth, 8);

    PerlinNoise2D waterNoise(noiseGridWidth, noiseGridDepth, seed + 100);
    PerlinNoise2D treeNoise(noiseGridWidth, noiseGridDepth, seed + 200);
    PerlinNoise2D rockNoise(noiseGridWidth, noiseGridDepth, seed + 300);
    PerlinNoise2D clayNoise(noiseGridWidth, noiseGridDepth, seed + 400);

    for (int y = 0; y < depth; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            float water = waterNoise.FractalNoise(x * waterScale, y * waterScale, octaveCount);
            float tree = treeNoise.FractalNoise(x * treeScale, y * treeScale, octaveCount);
            float rock = rockNoise.FractalNoise(x * rockScale, y * rockScale, octaveCount);
            float clay = clayNoise.FractalNoise(x * clayScale, y * clayScale, octaveCount);
            float dirt = clayNoise.FractalNoise(x * dirtScale, y * dirtScale, octaveCount);

            BlockId id = BlockId::Grass;

            // 우선순위 중요
            // Water가 먼저면 물 지역은 다른 자원으로 덮이지 않음
            if (water > 0.55f)
            {
                id = BlockId::Water;
            }
            else if (rock > 0.6f)
            {
                id = BlockId::Rock;
            }
            else if (dirt > 0.5f)
            {
                id = BlockId::Dirt;
            }
            else
            {
                id = BlockId::Grass;
            }


            SetBlock({ x, y, groundZ }, id);
            if (id == BlockId::Rock)
            {
                SetBlock({ x, y, groundZ + 1 }, id);
            }


            if (tree > 0.55f && (id == BlockId::Grass || id == BlockId::Dirt))
            {
                int ran = rand();
                if (ran % 2 == 0)
                {
                    SetBlock({ x, y, groundZ + 1 }, BlockId::Tree);

                }
                else
                {
                    SetBlock({ x, y, groundZ + 1 }, BlockId::OrcTree);

                }
            }
            else if (clay > 0.5f && (id == BlockId::Grass || id == BlockId::Dirt))
            {
                SetBlock({ x, y, groundZ + 1 }, BlockId::Clay);
            }
        }
    }
}

void BlockMap::MakeStartZone()
{
    int centerX = m_startPosition.x;
    int centerY = m_startPosition.y;

    int radius = 7;

    int left = centerX - radius;
    int right = centerX + radius;
    int top = centerY + radius;
    int bottom = centerY - radius;

    for (int nowX = left; nowX < right; nowX++)
    {
        for (int nowY = bottom; nowY < top; nowY++)
        {
            Vector2 v(nowX - centerX, nowY - centerY);
            if (v.Length() < radius)
            {
                SetBlock({ nowX,nowY,1 }, BlockId::Empty);
                Int3 pos{ nowX,nowY,0 };
                const Block* zeroFloorBlock = GetBlock(pos);
                if (zeroFloorBlock->blockId == BlockId::Water)
                {
                    SetBlock({ nowX,nowY,0 }, BlockId::Grass);

                }
            }
        }
    }
}


}