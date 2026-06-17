#include "ClearScene.h"

#include "Engine/Core/Debug.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Prefab/PrefabFactory.h"
#include "Engine/Components/Camera/Camara2D.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/TextRenderer.h"

#include "Game/Scripts/SceneChange/ClearSceneChange.h"

namespace Bisang
{
	void ClearScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp ClearScene \n");

		GameObject* camera = AddGameObject("Camera");
		SetSceneCamera(camera->GetComponent<Camera2D>());
		camera->GetComponent<Transform>()->SetScale({ 0.4, 0.4 });

		AddGameObject("AudioManager");

		GameObject* text = AddGameObject("TitleText");
		text->AddComponent<ClearSceneChange>();
		TextRenderer* textRender = text->GetComponent<TextRenderer>();
		textRender->SetText(L"<공주님은 비포장도로를 걷지않아!> 데모를 플레이해주셔서 감사합니다.\n\n                        메인화면으로 가기 [BACKSPACE]");
		text->GetComponent<Transform>()->SetPosition({ 500, 600, 0 });

		Transform* map = AddGameObject("BlockMap")
			->GetComponent<Transform>();

		map->SetPosition({ -600, 50, 0 });

	}

}