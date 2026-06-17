#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class MainSceneChange : public Script
	{
	public:
		MainSceneChange(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
	};
}