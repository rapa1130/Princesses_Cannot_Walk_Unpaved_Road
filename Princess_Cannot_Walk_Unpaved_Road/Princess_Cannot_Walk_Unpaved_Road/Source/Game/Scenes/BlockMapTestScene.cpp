#include "BlockMapTestScene.h"
#include "Engine/Core/Debug.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Prefab/PrefabFactory.h"
#include <iostream>

namespace Bisang
{
	void BlockMapTestScene::Initialize()
	{
		// 씬 진입 시 초기화 작업을 수행 ( 메모리, 리소스 등 )
		DEBUG_LOG("Initialize SamepleScene \n");

		m_resourceManager->LoadTexture(L"Assets/Textures/test.png")->SetPivot({ 0, -40, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/GrassBlock.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Water.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Rock.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Dirt.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Clay.png")->SetPivot({ 0, -20, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/Tree.png")->SetPivot({ 0, -30, 0 });
		m_resourceManager->LoadTexture(L"Assets/Textures/OrcTree.png")->SetPivot({ 0, -30, 0 });
	}

	void BlockMapTestScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp SamepleScene \n");

		std::cout << m_prefabFactory->Create("Player").get() << std::endl;
		//AddGameObject(m_prefabFactory->Create("Player"));

		////BlockMapPrefab* blockMapPrefab = new BlockMapPrefab();
		////AddGameObject(blockMapPrefab);
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