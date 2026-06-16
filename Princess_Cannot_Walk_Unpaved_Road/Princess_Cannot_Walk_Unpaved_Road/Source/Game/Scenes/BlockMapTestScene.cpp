#include "BlockMapTestScene.h"
#include "Engine/Core/Debug.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Prefab/PrefabFactory.h"
#include "Engine/Components/Camera/Camara2D.h"

#include <iostream>

namespace Bisang
{
	void BlockMapTestScene::Setup()
	{
		// 씬에 필요한 게임오브젝트와 컴포넌트 생성
		DEBUG_LOG("SetUp SamepleScene \n");
    
		AddGameObject("GameManager");
		AddGameObject("BlockMap");

		GameObject* camera = AddGameObject("Camera");
		SetSceneCamera(camera->GetComponent<Camera2D>());

		GameObject* monster = AddGameObject("BigMonster");

		AddGameObject("DebugOverlay");

		AddGameObject("AudioManager");
	}

}