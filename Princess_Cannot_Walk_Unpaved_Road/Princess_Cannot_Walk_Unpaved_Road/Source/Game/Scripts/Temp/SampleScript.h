#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class SampleScript : public Script
	{
	public:
		SampleScript(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
		void FixedUpdate() override;
	};
}