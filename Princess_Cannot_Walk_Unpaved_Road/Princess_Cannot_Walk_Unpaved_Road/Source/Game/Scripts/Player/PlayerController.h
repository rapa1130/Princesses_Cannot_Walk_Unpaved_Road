#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Math/Vector.h"
#include "Engine/Math/Int3.h"

#include "Engine/Input/InputCode.h"

#include <vector>

#include "Game/Scripts/Blocks/BlockId.h"


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
	class AudioManager;
	class Highlighter;

	class PlayerController : public Script
	{
	public:
		PlayerController(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;

		Vector2& GetFaceDir() { return m_faceDir; }
		Int3& GetCurrentPos() { return m_currentPos; }


		void SetKeyMapping(std::vector<KeyCode> keyMapping) { m_keyMapping = keyMapping; }

		void SetHighlight(Highlighter* highlighter) { m_highlighter = highlighter; }


	private:
		void Interact(const Int3& blockPos);
		void Move(float dT);
		void UpdateVelocity(float dT);
		void UpdateCurrentPos();
		bool UpdateInteratable(Int3& blockPos,BlockId& blockID);
		
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
		AudioManager* m_audio = nullptr;
		Highlighter* m_highlighter = nullptr;


		int m_playerZ = 1;
		Vector2 m_faceDir = { 0, 1 };
		Int3 m_currentPos;

		Vector3 m_velocity;
		float moveSpeed = 300;
		float m_maxSpeed = 200.f;
		float m_acceleration = 3000.f;
		float m_friction = 1000.0f;
		float m_collisionFrictionMultiplier = 0.75f;

		std::vector<KeyCode> m_keyMapping =
		{ KeyCode::Left,
		  KeyCode::Right,
		  KeyCode::Up,
		  KeyCode::Down,
		  KeyCode::Enter };
	};
}