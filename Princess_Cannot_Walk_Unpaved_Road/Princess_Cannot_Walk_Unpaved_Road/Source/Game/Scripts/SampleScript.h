#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class SampleScript : public Script
	{
	public:
		SampleScript(GameObject* ownerObj, Scene* scene) : Script(ownerObj, scene) {}

		void Start() override;
		void Update(float dT) override;
		void FixedUpdate() override;
	};
}