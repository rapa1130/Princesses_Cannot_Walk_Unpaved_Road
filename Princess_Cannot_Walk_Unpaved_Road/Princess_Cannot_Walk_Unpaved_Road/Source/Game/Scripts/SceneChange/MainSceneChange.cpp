#include "MainSceneChange.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"

#include "Game/Scripts/Map/BlockMapBackGroundGenerator.h"

namespace Bisang
{
	void MainSceneChange::Start()
	{
		BlockMap* map = FindGameObjectByName("BlockMap")
			->GetComponent<BlockMap>();

		BlockMapBackGroundGenerator generator;
		generator.GenerateMainBackGround(map);
	}

	void MainSceneChange::Update(float dT)
	{
		if (GetInputManager()->IsKeyPressed(KeyCode::Space))
		{
			ChangeScene("StoryScene");
		}
	}
}