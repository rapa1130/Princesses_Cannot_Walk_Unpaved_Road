#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class StorySceneChange : public Script
	{
	public:
		StorySceneChange(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
	};
}