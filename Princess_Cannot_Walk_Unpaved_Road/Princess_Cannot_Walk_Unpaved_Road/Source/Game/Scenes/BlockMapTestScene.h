#pragma once
#include "Engine/Scene/Scene.h"

namespace Bisang
{
	class BlockMapTestScene : public Scene
	{
	public:
		BlockMapTestScene(std::string sceneName, GameContext* context) : Scene(sceneName, context)
		{
		}

		void Finalize() override;
		void Setup() override;

	private:
		GameObject* m_player = nullptr;
	};
}