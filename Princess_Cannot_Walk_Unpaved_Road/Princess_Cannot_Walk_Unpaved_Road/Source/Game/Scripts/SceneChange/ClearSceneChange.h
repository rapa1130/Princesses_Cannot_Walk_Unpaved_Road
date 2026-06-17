#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class ClearSceneChange : public Script
	{
	public:
		ClearSceneChange(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
	};
}