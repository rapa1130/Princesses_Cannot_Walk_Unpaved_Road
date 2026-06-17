#include "ClearSceneChange.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"

#include "Game/Scripts/Audio/AudioManager.h"
#include "Game/Scripts/Map/BlockMapBackGroundGenerator.h"

namespace Bisang
{
	void ClearSceneChange::Start()
	{
		BlockMap* map = FindGameObjectByName("BlockMap")
			->GetComponent<BlockMap>();

		BlockMapBackGroundGenerator generator;
		generator.GenerateClearBackGround(map);

		FindGameObjectByName("AudioManager")
			->GetComponent<AudioManager>()
			->PlayClearBgm();
	}

	void ClearSceneChange::Update(float dT)
	{
		if (GetInputManager()->IsKeyPressed(KeyCode::Backspace))
		{
			ChangeScene("MainScene");
		}
	}
}