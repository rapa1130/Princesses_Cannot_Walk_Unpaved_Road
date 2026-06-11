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

		// 나중에 설정 코드로 뺄것임
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Front.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Back.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Left.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Right.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_BackLeft.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_BackRight.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_FrontLeft.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_FrontRight.png")->SetPivot({ -20, -40, 0 });

		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Left.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Right.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Back.png")->SetPivot({ -20, -40, 0 });
		m_context->resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Front.png")->SetPivot({ -20, -40, 0 });
	}

	void BlockMapTestScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp SamepleScene \n");
    
		AddGameObject("Player");
		AddGameObject("BlockMap");
		AddGameObject("DebugOverlay");

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