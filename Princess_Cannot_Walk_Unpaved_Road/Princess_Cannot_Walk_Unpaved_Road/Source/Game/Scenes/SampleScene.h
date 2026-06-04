#pragma once
#include "Engine/Scene/Scene.h"

namespace Bisang
{
	class SampleScene : public Scene
	{
	public:
		SampleScene(std::string sceneName, ResourceManager* resourceManager, InputManager* inputManager) :
			Scene(sceneName, resourceManager, inputManager) {
		}

		void Initialize() override;
		void Finalize() override;
		void Setup() override;
		void OnEnter() override;
		void OnExit() override;
	};
}