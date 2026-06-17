#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class OverSceneChange : public Script
	{
	public:
		OverSceneChange(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
	};
}