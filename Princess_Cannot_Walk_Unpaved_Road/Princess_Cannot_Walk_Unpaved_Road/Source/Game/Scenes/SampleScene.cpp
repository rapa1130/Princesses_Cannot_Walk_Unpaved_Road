#include "SampleScene.h"
#include "Engine/Object/GameObject.h"
#include "Game/Scripts/SampleScript.h"
#include"Engine/Core/Debug.h"
#include"Engine/Components/SpriteRenderer.h"
#include"Engine/Components/Transform.h"
#include"Engine/Components/LineRenderer.h"
#include"Engine/Components/TextRenderer.h"

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
		tranform->SetPosition(Vector3(500, 200, 0));
		
		//auto texture = m_resourceManager->LoadTexture(L"Assets/Textures/test.png");
		//spriteRenderer->SetSprite(texture);
		spriteRenderer->SetSprite(L"Assets/Textures/test.png");

		GameObject* lineObj = CreateGameObject("LineTest");
		LineRenderer* lineRenderer = lineObj->AddComponent<LineRenderer>();
		lineRenderer->SetColor(Color(1.0f,0,0,1.0f));
		lineRenderer->SetStartPosition(Vector3(300, 300, 0));
		lineRenderer->SetEndPosition(Vector3(800, 800, 0));
		lineRenderer->SetLineWidth(10.0f);


		GameObject* textObj = CreateGameObject("TextTest");
		TextRenderer* textRenderer = textObj->AddComponent<TextRenderer>();
		textRenderer->SetColor(Color::White);
		textRenderer->SetTextFormat(L"맑은 고딕", 24.0f);
		textRenderer->SetText(L"아 진짜 계란빵달다");
		Transform* textTrf = textRenderer->GetTransform();
		textTrf->SetPosition(Vector3(100, 100, 0));
		textTrf->SetScale(Vector2(1000.f, 100.f));

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