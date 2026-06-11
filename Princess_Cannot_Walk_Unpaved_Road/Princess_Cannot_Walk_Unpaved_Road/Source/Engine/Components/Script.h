#pragma once
#include "Engine/Components/Component.h"
#include <string>

namespace Bisang
{
	class GameObject;
	class InputManager;

	class Script : public Component
	{
	public:
		Script(GameObject* ownerObj) : Component(ownerObj) {}
		
		GameObject* Instantiate(const std::string& prefabName) const;
		GameObject* FindGameObjectByName(const std::string& name) const;
		InputManager* GetInputManager() const;
		

		virtual void Start() {}
		virtual void Update(float dT) {}
		virtual void FixedUpdate() {}
	};
}