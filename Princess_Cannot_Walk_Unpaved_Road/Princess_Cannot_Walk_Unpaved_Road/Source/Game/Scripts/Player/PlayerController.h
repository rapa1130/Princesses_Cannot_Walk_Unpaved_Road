#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Math/Vector.h"

#define PlayerAnimCount 8

namespace Bisang
{
	class Transform;
	class InputManager;
	class BlockMap;
	class SpriteRenderer;
	class BoxCollider;
	class Animator;
	class BlockObjectInfoTable;

	class PlayerController : public Script
	{
	public:
		PlayerController(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
		void FixedUpdate() override;
		

		bool CanMoveTo(const Vector3& worldPos) const;
		void SetToStartPostion();

	private:
		void Move(float dT);
		void UpdateVelocity(float dT);
		bool CanMoveBoxArea(const Vector3& center);
		void UpdateAnimation(); // юс╫ц

		void InitializeAnimator();

	private:
		BlockObjectInfoTable* m_blockObjectInfoTable;
		Transform* m_transform = nullptr;
		InputManager* m_input = nullptr;
		BlockMap* m_blockMap = nullptr;
		int playerZ = 1;

		Vector3 m_velocity;
		float moveSpeed = 300;
		float m_maxSpeed = 300.f;
		float m_acceleration =100.f;
		float m_friction = 10.0f;

		BoxCollider* m_BoxCol = nullptr;

		SpriteRenderer* m_spriteRenderer = nullptr;
		Animator* m_animator = nullptr;

		std::wstring m_nameArr[PlayerAnimCount] = {
			L"FrontLeft",
			L"FrontRight",
			L"BackLeft",
			L"BackRight",
			L"Front",
			L"Back",
			L"Left",
			L"Right",
		};
	};
}