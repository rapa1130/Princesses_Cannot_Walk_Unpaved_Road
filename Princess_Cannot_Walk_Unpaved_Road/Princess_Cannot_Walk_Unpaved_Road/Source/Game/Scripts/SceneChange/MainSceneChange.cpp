#include "MainSceneChange.h"
#include "Engine/Input/InputManager.h"

namespace Bisang
{
	void MainSceneChange::Update(float dT)
	{
		if (GetInputManager()->IsKeyPressed(KeyCode::Space))
		{
			ChangeScene("PlayScene");
		}
	}
}