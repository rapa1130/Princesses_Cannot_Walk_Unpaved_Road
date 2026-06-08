#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class BlockMap;
	class InputManager;

	class BlockMapTest : public Script
	{
	public:
		BlockMapTest(GameObject* ownerObj, Scene* scene) : Script(ownerObj, scene) {}

		void Start() override;
		void Update(float dT) override;
		void FixedUpdate() override;

	private:
		BlockMap* m_blockMap = nullptr;
		InputManager* m_input = nullptr;
		float addPower = 10.f;
	};


}