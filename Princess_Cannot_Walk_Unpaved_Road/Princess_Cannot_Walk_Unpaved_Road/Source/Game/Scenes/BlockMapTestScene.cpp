#include "BlockMapTestScene.h"
#include "Engine/Core/Debug.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Prefab/PrefabFactory.h"
#include <iostream>

namespace Bisang
{
	void BlockMapTestScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp SamepleScene \n");
    
		AddGameObject("Player");
		AddGameObject("BlockMap");
		AddGameObject("DebugOverlay");

	}

	void BlockMapTestScene::Finalize()
	{
		// 씬이 사용하던 자원을 정리하고 종료 처리
		DEBUG_LOG("OnEnter Finalize \n");
	}
}