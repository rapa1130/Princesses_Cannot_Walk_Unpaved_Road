#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Math/Int3.h"

namespace Bisang
{
	class BlockMap;

	class BlockMapGenerator : public Script
	{
		BlockMapGenerator(GameObject* ownerObj) : Script(ownerObj) {}
		void Generate(BlockMap* blockMap);
		void GenerateProceduralMap(unsigned int seed, int width, int height, int depth);
	};
}
