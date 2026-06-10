#pragma once
#include "Engine/Components/Component.h"
#include <string>

namespace Bisang
{
	class GameApp;
	class Component;

	class Script : public Component
	{
	public:
		Script(GameObject* ownerObj) : Component(ownerObj) {}

		virtual void Start() {}
		virtual void Update(float dT) {}
		virtual void FixedUpdate() {}
	};
}