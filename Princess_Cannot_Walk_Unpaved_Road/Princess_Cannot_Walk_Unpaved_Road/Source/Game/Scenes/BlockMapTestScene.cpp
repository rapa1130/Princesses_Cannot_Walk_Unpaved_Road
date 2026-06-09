#include "BlockMapTestScene.h"
#include "Engine/Object/GameObject.h"
#include "Game/Scripts/PlayerController.h"
#include "Engine/Core/Debug.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Components/Transform.h"
#include <iostream>
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/BlockMap/BlockMapRenderer.h"
#include "Engine/Core/Layer.h"
#include "Game/Scripts/BlockMapTest.h"
#include "Engine/Components/TextRenderer.h"
#include "Engine/Resource/ResourceManager.h"


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
		
		bMap->InitMap(30, 30, 30);


		for (int i = 0; i < 10; i++)
		{
			for (int ii = 0; ii < 10; ii++)
			{
				for (int iii = 0; iii <= 0; iii++)
				{
					bMap->SetBlock({ i, ii, iii }, BlockId::Grass);
				}
			}
		}
		srand(time(NULL));
		bMap->GenerateProceduralMap(rand());
		bMap->SetBlock({ 1, 1, 1 }, BlockId::Grass);
		bMap->SetBlock({ 3, 1, 1 }, BlockId::Grass);
		bMap->SetBlock({ 1, 3, 1 }, BlockId::Grass);

		m_resourceManager->LoadTexture(L"Assets/Textures/GrassBlock.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Water.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Rock.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Dirt.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Clay.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Tree.png")->SetPivot({ 0, -30, 0 });
		BlockMapRenderer* bMapR = blockMap->AddComponent<BlockMapRenderer>();
		bMapR->SetLayer(Layer::Iso);
		bMapR->SetBlockMap(bMap);
		
		DEBUG_LOG("SetUp SamepleScene \n");

		Transform* bMapT = blockMap->GetComponent<Transform>();
		bMapT->SetScale({ 0.5, 0.5});
		bMapT->SetPosition({ 100, 900, 0 });

		blockMap->AddComponent<BlockMapTest>();

		//////////////////////////////////////////////////////////////////////////////////////
		GameObject* playerObj = CreateGameObject("Player");
		Transform* tf = playerObj->GetComponent<Transform>();
		tf->SetScale({ 0.2, 0.2 });
		tf->SetPosition({ 200, 800, 1 });


		SpriteRenderer* sr = playerObj->AddComponent<SpriteRenderer>();
		sr->SetLayer(Layer::Iso);
		m_resourceManager->LoadTexture(L"Assets/Textures/test.png")->SetPivot({ 0, -40, 0 });
		sr->SetSprite(L"Assets/Textures/test.png");

		playerObj->AddComponent<PlayerController>();

		//////////////////////////////////////////////////////////////////////////////////////
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