#include "StoryScene.h"

#include "Engine/Core/Debug.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Prefab/PrefabFactory.h"
#include "Engine/Components/Camera/Camara2D.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	void StoryScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp MainScene \n");

		GameObject* camera = AddGameObject("Camera");
		SetSceneCamera(camera->GetComponent<Camera2D>());
		camera->GetComponent<Transform>()->SetScale({ 0.4, 0.4 });

		AddGameObject("AudioManager");

		AddGameObject("Title");
		AddGameObject("TitleText");
		

	}

}