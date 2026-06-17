#include "OverScene.h"

#include "Engine/Core/Debug.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Prefab/PrefabFactory.h"
#include "Engine/Components/Camera/Camara2D.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/TextRenderer.h"

namespace Bisang
{
	void OverScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp StoryScene \n");

		GameObject* camera = AddGameObject("Camera");
		SetSceneCamera(camera->GetComponent<Camera2D>());

		AddGameObject("AudioManager");

		AddGameObject("Cartoon");

		GameObject* text = AddGameObject("TitleText");

		TextRenderer* textRender = text->GetComponent<TextRenderer>();
		textRender->SetText(L"게임 진행하기 [SPACE]");

		Transform* textTransform = text->GetComponent<Transform>();
		textTransform->SetPosition({ 1450,900,0 });

	}

}