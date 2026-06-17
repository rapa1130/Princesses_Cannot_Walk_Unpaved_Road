#include "OverScene.h"

#include "Engine/Core/Debug.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Prefab/PrefabFactory.h"
#include "Engine/Components/Camera/Camara2D.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/TextRenderer.h"

#include "Game/Scripts/SceneChange/OverSceneChange.h"

namespace Bisang
{
	void OverScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp OverScene \n");

		GameObject* camera = AddGameObject("Camera");
		SetSceneCamera(camera->GetComponent<Camera2D>());
		camera->GetComponent<Transform>()->SetScale({ 0.4, 0.4 });

		AddGameObject("AudioManager");

		GameObject* text = AddGameObject("TitleText");
		text->AddComponent<OverSceneChange>();
		TextRenderer* textRender = text->GetComponent<TextRenderer>();
		textRender->SetText(L"재시작 [SPACE]\n메인화면 [BACKSPACE]");
		text->GetComponent<Transform>()->SetPosition({ 800, 600, 0 });
		
		Transform* map = AddGameObject("BlockMap")
			->GetComponent<Transform>();

		map->SetPosition({ -500, 50, 0 });

	}

}