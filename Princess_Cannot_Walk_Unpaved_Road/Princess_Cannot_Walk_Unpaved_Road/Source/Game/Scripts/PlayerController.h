#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Math/Vector.h"

namespace Bisang
{
	class Transform;
	class InputManager;

	class PlayerController : public Script
	{
	public:
		PlayerController(GameObject* ownerObj, Scene* scene) : Script(ownerObj, scene) {}

		void Start() override;
		void Update(float dT) override;
		void FixedUpdate() override;

	private:
		Transform* m_transform = nullptr;
		InputManager* m_input = nullptr;
		Vector3 m_dir;
		float moveSpeed = 3;
	};
}