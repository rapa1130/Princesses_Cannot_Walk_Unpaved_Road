#include "SampleScene.h"
#include "Engine/Object/GameObject.h"
#include "Game/Scripts/temp/SampleScript.h"
#include"Engine/Core/Debug.h"
#include"Engine/Components/SpriteRenderer.h"
#include"Engine/Components/Transform.h"
#include"Engine/Components/LineRenderer.h"
#include"Engine/Components/TextRenderer.h"

namespace Bisang
{

	void SampleScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp SamepleScene \n");

	}

	void SampleScene::Finalize()
	{
		// 씬이 사용하던 자원을 정리하고 종료 처리
		DEBUG_LOG("OnEnter Finalize \n");

	}
}