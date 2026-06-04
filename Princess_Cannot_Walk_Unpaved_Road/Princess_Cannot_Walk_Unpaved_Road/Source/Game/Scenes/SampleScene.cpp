#include "SampleScene.h"
#include "Engine/Object/GameObject.h"
#include "Game/Scripts/SampleScript.h"

namespace Bisang
{
	void SampleScene::Initialize()
	{
		// 씬 진입 시 초기화 작업을 수행 ( 메모리, 리소스 등 )
	}

	void SampleScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		m_player = CreateGameObject("Player");
		m_player->AddComponent<SampleScript>();
	}

	void SampleScene::OnEnter()
	{
		// 씬 진입 시 호출 / 게임 로직에 사용
	}

	void SampleScene::OnExit()
	{
		// 씬 종료 시 호출 / 게임 로직에 사용
	}

	void SampleScene::Finalize()
	{
		// 씬이 사용하던 자원을 정리하고 종료 처리
	}
}