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
	class PlayerStatus;

	class PlayerController : public Script
	{
	public:
		PlayerController(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
		
		void SetToStartPostion();

	private:
		void Interact();
		void Move(float dT);
		void UpdateVelocity(float dT);
		bool CanMoveBoxArea(const Vector3& center);
		bool CanMoveTo(const Vector3& worldPos) const;

	private:
		BlockObjectInfoTable* m_blockObjectInfoTable;
		Transform* m_transform = nullptr;
		InputManager* m_input = nullptr;
		BlockMap* m_blockMap = nullptr;
		SpriteRenderer* m_spriteRenderer = nullptr;
		BoxCollider* m_BoxCol = nullptr;
		PlayerStatus* m_playerStatus = nullptr;


		int playerZ = 1;

		Vector3 m_velocity;
		float moveSpeed = 300;
		float m_maxSpeed = 200.f;
		float m_acceleration = 3000.f;
		float m_friction = 1000.0f;
	};
}