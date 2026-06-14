#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class BlockMap;
	class InputManager;

	class BlockMapTest : public Script
	{
	public:
		BlockMapTest(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
		void FixedUpdate() override;

	private:
		BlockMap* m_blockMap = nullptr;
		InputManager* m_input = nullptr;
		float addPower = 30.f;
	};


}