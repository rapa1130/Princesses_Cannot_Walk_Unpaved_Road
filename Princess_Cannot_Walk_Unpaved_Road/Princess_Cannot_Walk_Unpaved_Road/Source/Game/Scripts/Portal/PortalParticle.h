#pragma once

#include "Engine/Components/Script.h"
#include "Engine/Math/Int3.h"
#include "Engine/Math/Vector.h"

#include <vector>

namespace Bisang
{
	class SpriteRenderer;
	class Transform;
	class BlockMap;

	class PortalParticle : public Script
	{
		public:
			PortalParticle(GameObject* ownerObj) : Script(ownerObj) {}

			void Start() override;
			void Update(float dT) override;

			void CreateParticle();
			
			void SetPosition(const Int3& pos) { m_pos = pos; }
			Int3 GetPosition() const { return m_pos; }

			void SetRisingSpeed(float speed);
			float GetRisingSpeed() const;

		private:

			SpriteRenderer* m_spriteRenderer = nullptr;

			Vector2 m_startOffset; // 포탈 기준 시작 위치, 아래쪽
			Vector2 m_endOffset;   // 포탈 기준 도착 위치, 위쪽

			float m_t;

			float m_speed;         // 파티클별 상승 속도
			float m_alphaPhase;    // 깜빡임용, 선택

			float m_risingSpeed = 0.4f;
			float m_risingDistance = 40.f;
			float m_randRadius = 20.0f;

			Int3 m_pos;
			Vector3 m_worldPos;
			Transform* m_transform = nullptr;
			BlockMap* m_blockMap = nullptr;

	};
}
