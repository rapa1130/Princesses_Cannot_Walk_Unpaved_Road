#pragma once
#include "Engine/Components/Component.h"
#include "Engine/Math/Vector.h"

namespace Bisang
{
	class Transform : public Component
	{
	public:
		Transform(GameObject* ownerObj);

		void SetPosition(Vector3 pos) { m_pos = pos; }
		void SetScale(Vector2 scale) { m_scale = scale; }
		void SetRotation(float rotation) { m_rotation = rotation; }

		Vector3 GetPosition() const { return m_pos; }
		Vector2 GetScale() const { return m_scale; }
		float GetRotation() const { return m_rotation; }

		/**
		 * @brief 월드 좌표계 기준 위치를 반환한다.
		 *
		 * 부모 오브젝트가 없는 경우 자신의 로컬 위치를 반환한다.
		 * 부모 오브젝트가 있는 경우 월드 위치를 반환한다.
		 *
		 * @return 계산된 월드 위치
		 */
		Vector3 GetWorldPosition();

		/**
		 * @brief 현재 위치에 이동 벡터를 더한다.
		 *
		 * @param[in] moveVector 이동시킬 거리 벡터
		 */
		void Translate(Vector3 moveVector)
		{
			m_pos += moveVector;
		}

		/**
		 * @brief 현재 회전값에 각도를 더한다.
		 *
		 * @param[in] angle 추가할 회전 각도 (Degree)
		 */
		void Rotate(float angle)
		{
			m_rotation += angle;
		}

		/**
		 * @brief 현재 스케일에 스케일 값을 더한다.
		 *
		 * @param[in] scale 추가할 스케일 값
		 */
		void AddScale(Vector2 scale)
		{
			m_scale += scale;
		}

	private:
		Vector3 m_pos = { 0.0f, 0.0f, 0.0f };     // 위치
		Vector2 m_scale = { 1.0f, 1.0f };   // 배율
		float m_rotation = 0.0f;            // 0 = 오른쪽, 90 = 위, 180 = 왼쪽, 270 = 아래
	};
}