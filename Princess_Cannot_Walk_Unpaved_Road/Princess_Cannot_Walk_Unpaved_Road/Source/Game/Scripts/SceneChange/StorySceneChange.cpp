#include "StorySceneChange.h"

#include "Engine/Input/InputManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"

#include "Game/Scripts/Map/BlockMapBackGroundGenerator.h"
#include "Game/Scripts/Audio/AudioManager.h"

namespace Bisang
{
	void StorySceneChange::Start()
	{
		FindGameObjectByName("AudioManager")
			->GetComponent<AudioManager>()
			->PlayStoryBgm();
	}

	void StorySceneChange::Update(float dT)
	{
		if (GetInputManager()->IsKeyPressed(KeyCode::Space))
		{
			ChangeScene("PlayScene");
		}
	}
}