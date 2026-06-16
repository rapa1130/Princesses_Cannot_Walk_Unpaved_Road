#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Math/Int3.h"
#include "Engine/Math/Vector.h"

namespace Bisang
{
	class BlockMap;
	class Transform;
	class SpriteRenderer;
	class CameraController;

	class MonsterController : public Script
	{
	public:
		MonsterController(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;

		void DestructArea();
		void SetDestructRangeY(int rangeY);

		void SetWorldPosbyBlockY(int blockY);

		void Jump(float dT);
		void SetMoveTerm(float moveTerm);
		void SetLeapDistance(int dist);
		void SetJumpDuration(float duration);
		void SetJumpHeight(float height);


		void ShakeCameraByDist();
		void SetMinShakeDistY(int minShakeDistY); //카메라 셰이크 효과 적용하는 최소 y축 거리
		void SetShakePower(int shakePower); 


	private:
		BlockMap* m_blockMap = nullptr;
		Transform* m_transform = nullptr;
		SpriteRenderer* m_spriteRenderer = nullptr;
		CameraController* m_camCtrl = nullptr;


		float m_moveTerm;
		int m_leapDistance;

		Int3 m_position;

		Vector3 m_jumpStartPos;
		Vector3 m_jumpTargetPos;

		float m_jumpTimer = 0.0f;
		float m_jumpDuration = 0.7f;
		float m_jumpHeight = 60.0f;

		bool m_isJumping = false;

		int m_destructRangeY = 3;

		int m_minShakeDistY;
		float m_shakePower;
	};


}