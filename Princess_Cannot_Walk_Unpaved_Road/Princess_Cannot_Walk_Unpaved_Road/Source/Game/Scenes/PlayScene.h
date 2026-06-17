#pragma once
#include "Engine/Scene/Scene.h"

namespace Bisang
{
	class PlayScene : public Scene
	{
	public:
		PlayScene(std::string sceneName, SceneManager* sceneManager, GameContext* context) 
			: Scene(sceneName, sceneManager, context)
		{
		}
		
		void Setup() override;
	};
}