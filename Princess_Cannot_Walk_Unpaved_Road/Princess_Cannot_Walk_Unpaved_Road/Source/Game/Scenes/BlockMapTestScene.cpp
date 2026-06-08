#include "BlockMapTestScene.h"
#include "Engine/Object/GameObject.h"
#include "Game/Scripts/SampleScript.h"
#include"Engine/Core/Debug.h"
#include"Engine/Components/SpriteRenderer.h"
#include"Engine/Components/Transform.h"
#include <iostream>
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/BlockMap/BlockMapRenderer.h"
#include "Engine/Core/Layer.h"

namespace Bisang
{
	void BlockMapTestScene::Initialize()
	{
		// 씬 진입 시 초기화 작업을 수행 ( 메모리, 리소스 등 )
		DEBUG_LOG("Initialize SamepleScene \n");

	}

	void BlockMapTestScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp SamepleScene \n");

		GameObject* blockMap = CreateGameObject("BlockMap");
		BlockMap* bMap = blockMap->AddComponent<BlockMap>();
		
		bMap->SetAngle(45, 35);
		bMap->InitMap(50, 50, 50);
		bMap->SetBlockSize(54, 54, 54);

		for (int i = 0; i < 10; i++)
		{
			for (int ii = 0; ii < 10; ii++)
			{
				for (int iii = 0; iii < 3; iii++)
				{
					bMap->SetBlock({ i, ii, iii }, BlockId::Grass);
				}
			}
		}
		
		bMap->SetBlock({ 0 ,0, 0 }, BlockId::Empty);

		BlockMapRenderer* bMapR = blockMap->AddComponent<BlockMapRenderer>();
		bMapR->SetLayer(Layer::Iso);
		bMapR->SetBlockMap(bMap);
		

		Transform* bMapT = blockMap->GetComponent<Transform>();
		bMapT->SetScale({ 0.1, 0.1 });
		bMapT->SetPosition({ 400, 200, 0 });





	}

	void BlockMapTestScene::OnEnter()
	{
		// 씬 진입 시 호출 / 게임 로직에 사용
		DEBUG_LOG("OnEnter SamepleScene \n");
	}

	void BlockMapTestScene::OnExit()
	{
		// 씬 종료 시 호출 / 게임 로직에 사용
		DEBUG_LOG("OnEnter On Exit \n");

	}

	void BlockMapTestScene::Finalize()
	{
		// 씬이 사용하던 자원을 정리하고 종료 처리
		DEBUG_LOG("OnEnter Finalize \n");

	}
}