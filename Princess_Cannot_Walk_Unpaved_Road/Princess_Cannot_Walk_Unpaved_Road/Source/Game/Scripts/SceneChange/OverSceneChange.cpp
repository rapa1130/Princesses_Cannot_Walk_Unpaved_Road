#include "OverSceneChange.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"

#include "Game/Scripts/Map/BlockMapBackGroundGenerator.h"
#include "Game/Scripts/Audio/AudioManager.h"

namespace Bisang
{
	void OverSceneChange::Start()
	{
		BlockMap* map = FindGameObjectByName("BlockMap")
			->GetComponent<BlockMap>();

		BlockMapBackGroundGenerator generator;
		generator.GenerateGameOverBackGround(map);

		FindGameObjectByName("AudioManager")
			->GetComponent<AudioManager>()
			->PlayOverSound();
	}

	void OverSceneChange::Update(float dT)
	{
		if (GetInputManager()->IsKeyPressed(KeyCode::Space))
		{
			ChangeScene("PlayScene");
		}

		if (GetInputManager()->IsKeyPressed(KeyCode::Backspace))
		{
			ChangeScene("MainScene");
		}
	}
}