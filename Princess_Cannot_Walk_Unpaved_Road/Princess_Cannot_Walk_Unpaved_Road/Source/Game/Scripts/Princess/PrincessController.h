#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Math/Vector.h"
#include "Engine/Math/Int3.h"

#define PlayerAnimCount 8

namespace Bisang
{
	class Transform;
	class BlockMap;
	class SpriteRenderer;
	class Animator;
	class BlockObjectInfoTable;
	class RailManager;

	class PrincessController : public Script
	{
	public:
		PrincessController(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;

		float GetMoveSpeed() const;
		void SetMoveSpeed(float speed);

		Int3 GetMoveDirection() const;

	private:
		void Move(const Vector3& nowWorldPos, const Vector3& targetWorldPos, float dT);

		bool HasReachRoadEnd() const;
		bool HasReachedCurrentRoadPoint(const Vector3& nowWorldPos, const Vector3& targetWorldPos) const;

	private:
		BlockObjectInfoTable* m_blockObjectInfoTable;
		Transform* m_transform = nullptr;
		InputManager* m_input = nullptr;
		BlockMap* m_blockMap = nullptr;
		SpriteRenderer* m_spriteRenderer = nullptr;
		RailManager* m_railManager = nullptr;


		int playerZ = 1;

		int m_nowWalkingRailIndex = 0;

		Int3 m_nowMoveDir;

		Vector3 m_velocity;
		float m_moveSpeed = 30.f;
	};
}