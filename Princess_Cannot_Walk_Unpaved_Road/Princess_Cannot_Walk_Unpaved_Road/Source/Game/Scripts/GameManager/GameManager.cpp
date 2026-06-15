#include "GameManager.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMapRenderer.h"

#include "Game/Scripts/Blocks/BlockInfoProvider.h"
#include "Game/Scripts/Map/BlockMapGenerator.h"

#include <random>

namespace Bisang
{
	void GameManager::Start()
	{
		m_blockMap = FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();

		//*************************************************
		// 블럭 맵 렌더러에 blockinfotable 주입 -> 텍스처 매핑가능
		// * 현재 엔진이 게임코드에 의존 나중에 수정 필요
		//************************************************* 
		BlockMapRenderer* blockMapRenderer = FindGameObjectByName("BlockMap")->GetComponent<BlockMapRenderer>();
		BlockObjectInfoProvider* blockMapInfoProvider = FindGameObjectByName("BlockMap")->GetComponent<BlockObjectInfoProvider>();
		blockMapRenderer->SetBlockObjectInfoTable(blockMapInfoProvider->GetTable());


		//*************************************************
		// 랜덤 맵 생성
		//************************************************* 
		GenerateMap();
	}

	void GameManager::Update(float dT)
	{

	}

	void GameManager::GenerateMap()
	{
		unsigned int seed = CreateRandomSeed();   // 시드 생성
		int width = 50;
		int height = 50;
		int depth = 3;
		m_startPosition = { width / 2, 10 , m_playerZ };
		m_startPosition = { width / 2, 40 , m_playerZ };

		BlockMapGenerator mapGenerator;
		mapGenerator.GenerateProceduralMap(
			m_blockMap,
			seed,
			width,
			height,
			depth,
			m_startPosition,
			m_endPosition);
	}

	unsigned int GameManager::CreateRandomSeed() const
	{
		std::random_device rd;
		return rd();
	}
}