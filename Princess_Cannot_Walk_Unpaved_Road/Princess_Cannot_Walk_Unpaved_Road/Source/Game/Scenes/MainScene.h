#pragma once
#include "Engine/Scene/Scene.h"

namespace Bisang
{
	class MainScene : public Scene
	{
	public:
		MainScene(std::string sceneName, SceneManager* sceneManager, GameContext* context)
			: Scene(sceneName, sceneManager, context)
		{
		}

		void Setup() override;
	};
}