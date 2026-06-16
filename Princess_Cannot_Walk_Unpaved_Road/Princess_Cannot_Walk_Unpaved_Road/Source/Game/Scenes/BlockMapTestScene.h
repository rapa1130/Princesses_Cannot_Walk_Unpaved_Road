#pragma once
#include "Engine/Scene/Scene.h"

namespace Bisang
{
	class BlockMapTestScene : public Scene
	{
	public:
		BlockMapTestScene(std::string sceneName, SceneManager* sceneManager, GameContext* context) 
			: Scene(sceneName, sceneManager, context)
		{
		}
		
		void Setup() override;

	private:
		GameObject* m_player = nullptr;
	};
}