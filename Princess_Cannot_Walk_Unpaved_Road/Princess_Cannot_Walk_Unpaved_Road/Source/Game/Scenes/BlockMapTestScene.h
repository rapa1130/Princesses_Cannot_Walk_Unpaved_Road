#pragma once
#include "Engine/Scene/Scene.h"

namespace Bisang
{
	class BlockMapTestScene : public Scene
	{
	public:
		BlockMapTestScene(std::string sceneName, ResourceManager* resourceManager, InputManager* inputManager) :
			Scene(sceneName, resourceManager, inputManager) {
		}

		void Initialize() override;
		void Finalize() override;
		void Setup() override;
		void OnEnter() override;
		void OnExit() override;

	private:
		GameObject* m_player = nullptr;
	};
}