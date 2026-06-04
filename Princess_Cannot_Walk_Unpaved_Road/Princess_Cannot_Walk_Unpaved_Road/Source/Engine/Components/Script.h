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
		Script(GameObject* ownerObj, Scene* scene) : Component(ownerObj, scene) {}

		virtual void Start() {}
		virtual void Update(float dT) {}
		virtual void FixedUpdate() {}
	};
}