#include "MainScene.h"

#include "Engine/Core/Debug.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Prefab/PrefabFactory.h"
#include "Engine/Components/Camera/Camara2D.h"

namespace Bisang
{
	void MainScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp MainScene \n");

		GameObject* camera = AddGameObject("Camera");
		SetSceneCamera(camera->GetComponent<Camera2D>());

		AddGameObject("AudioManager");
		AddGameObject("Title");
	}

}