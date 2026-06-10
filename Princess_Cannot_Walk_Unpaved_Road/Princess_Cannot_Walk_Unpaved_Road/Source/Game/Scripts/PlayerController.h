#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Math/Vector.h"

namespace Bisang
{
	class Transform;
	class InputManager;
	class BlockMap;

	class PlayerController : public Script
	{
	public:
		PlayerController(GameObject* ownerObj, Scene* scene) : Script(ownerObj, scene) {}

		void Start() override;
		void Update(float dT) override;
		void FixedUpdate() override;
		

		bool CanMoveTo(const Vector3& worldPos) const;
		void SetToStartPostion();

	private:
		void Move(float dT);
		void UpdateVelocity(float dT);

	private:
		Transform* m_transform = nullptr;
		InputManager* m_input = nullptr;
		BlockMap* m_blockMap = nullptr;
		int playerZ = 1;

		//Vector2 m_dir;
		Vector3 m_velocity;
		float moveSpeed = 300;
		float m_maxSpeed = 300.f;
		float m_acceleration =100.f;
		float m_friction = 10.0f;
	};
}