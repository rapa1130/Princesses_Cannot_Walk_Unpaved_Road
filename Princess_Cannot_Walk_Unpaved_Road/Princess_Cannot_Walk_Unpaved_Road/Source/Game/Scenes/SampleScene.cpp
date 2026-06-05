#include "SampleScene.h"
#include "Engine/Object/GameObject.h"
#include "Game/Scripts/SampleScript.h"
#include"Engine/Core/Debug.h"
#include"Engine/Components/SpriteRenderer.h"
#include"Engine/Components/Transform.h"
#include"Engine/Components/LineRenderer.h"

namespace Bisang
{
	void SampleScene::Initialize()
	{
		// 씬 진입 시 초기화 작업을 수행 ( 메모리, 리소스 등 )
		DEBUG_LOG("Initialize SamepleScene \n");

	}

	void SampleScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp SamepleScene \n");


		m_player = CreateGameObject("Player");
		m_player->AddComponent<SampleScript>();
		SpriteRenderer* spriteRenderer = m_player->AddComponent<SpriteRenderer>();
		Transform* tranform = m_player->GetComponent<Transform>();
		tranform->SetScale(Vector2(1, 1));
		tranform->SetPosition(Vector2(500, 200));
		
		auto texture = m_resourceManager->LoadTexture(L"Source/Assets/Textures/test.png");
		spriteRenderer->SetSprite(texture);

		m_player = CreateGameObject("LineTest");
		LineRenderer* lineRenderer =  m_player->AddComponent<LineRenderer>();
		lineRenderer->SetColor(Color(1.0f,0,0,1.0f));
		lineRenderer->SetStartPosition(Vector2(300, 300));
		lineRenderer->SetEndPosition(Vector2(800, 800));
		lineRenderer->SetLineWidth(10.0f);
	}

	void SampleScene::OnEnter()
	{
		// 씬 진입 시 호출 / 게임 로직에 사용
		DEBUG_LOG("OnEnter SamepleScene \n");
	}

	void SampleScene::OnExit()
	{
		// 씬 종료 시 호출 / 게임 로직에 사용
		DEBUG_LOG("OnEnter On Exit \n");

	}

	void SampleScene::Finalize()
	{
		// 씬이 사용하던 자원을 정리하고 종료 처리
		DEBUG_LOG("OnEnter Finalize \n");

	}
}