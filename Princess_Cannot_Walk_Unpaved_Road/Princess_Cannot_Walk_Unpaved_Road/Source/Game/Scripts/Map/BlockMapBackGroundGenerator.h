#pragma once

namespace Bisang
{
	class BlockMap;

	class BlockMapBackGroundGenerator
	{
	public:
		void GenerateMainBackGround(BlockMap* map);
		void GenerateGameOverBackGround(BlockMap* map);
		void GenerateClearBackGround(BlockMap* map);
	};
}