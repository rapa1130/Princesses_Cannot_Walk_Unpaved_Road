#include "BlockMapTestScene.h"
#include "Engine/Object/GameObject.h"
#include "Game/Scripts/PlayerController.h"
#include"Engine/Core/Debug.h"
#include"Engine/Components/SpriteRenderer.h"
#include"Engine/Components/Transform.h"
#include <iostream>
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/BlockMap/BlockMapRenderer.h"
#include "Engine/Core/Layer.h"
#include "Game/Scripts/BlockMapTest.h"


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
		
		bMap->SetAngle(80.0f, 30.0f);
		bMap->InitMap(30, 30, 30);
		bMap->SetBlockSize(120,120, 120);

		for (int i = 0; i < 10; i++)
		{
			for (int ii = 0; ii < 5; ii++)
			{
				for (int iii = 1; iii < 2; iii++)
				{
					bMap->SetBlock({ i, ii, iii }, BlockId::Grass);
				}
			}
		}

		blockMap->AddComponent<BlockMapTest>();
	

		BlockMapRenderer* bMapR = blockMap->AddComponent<BlockMapRenderer>();
		bMapR->SetLayer(Layer::Iso);
		bMapR->SetBlockMap(bMap);
		

		Transform* bMapT = blockMap->GetComponent<Transform>();
		bMapT->SetScale({ 0.8, 0.8});
		bMapT->SetPosition({ 400, 0, 0 });

		//////////////////////////////////////////////////////////////////////////////////////
		GameObject* playerObj = CreateGameObject("Player");
		Transform* tf = playerObj->GetComponent<Transform>();
		tf->SetScale({ 0.2, 0.2 });
		SpriteRenderer* sr = playerObj->AddComponent<SpriteRenderer>();
		sr->SetLayer(Layer::Iso);
		sr->SetSprite(L"Assets/Textures/test.png");

		
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