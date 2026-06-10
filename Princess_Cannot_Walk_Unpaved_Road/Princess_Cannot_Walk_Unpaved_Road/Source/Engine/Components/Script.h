#pragma once
#include "Engine/Components/Component.h"
#include <string>

namespace Bisang
{
	class GameApp;
	class Component;
	class Scene;

	class Script : public Component
	{
	public:
		Script(GameObject* ownerObj);

		virtual void Start() {}
		virtual void Update(float dT) {}
		virtual void FixedUpdate() {}

	protected:
		Scene* m_scene = nullptr;
	};
}