#include "Collision.h"

#include "Engine/Components/Collider/Collider.h"
#include "Engine/Components/Collider/BoxCollider.h"
#include "Engine/Components/Collider/CircleCollider.h"
#include "Engine/Math/Vector.h"
#include "Engine/Math/Math.h"

#include <cmath>

namespace Bisang
{
	bool Collision::Check(Collider* lhs, Collider* rhs)
	{
		if (lhs == nullptr || rhs == nullptr)
			return false;

		ColliderType leftType = lhs->GetType();
		ColliderType rightType = rhs->GetType();

		if (leftType == ColliderType::Circle &&
			rightType == ColliderType::Circle)
		{
			return CheckCircleCircle(
				static_cast<CircleCollider*>(lhs),
				static_cast<CircleCollider*>(rhs)
			);
		}

		if (leftType == ColliderType::Box &&
			rightType == ColliderType::Box)
		{
			return CheckBoxBox(
				static_cast<BoxCollider*>(lhs),
				static_cast<BoxCollider*>(rhs)
			);
		}

		if (leftType == ColliderType::Circle &&
			rightType == ColliderType::Box)
		{
			return CheckCircleBox(
				static_cast<CircleCollider*>(lhs),
				static_cast<BoxCollider*>(rhs)
			);
		}

		if (leftType == ColliderType::Box &&
			rightType == ColliderType::Circle)
		{
			return CheckCircleBox(
				static_cast<CircleCollider*>(rhs),
				static_cast<BoxCollider*>(lhs)
			);
		}

		return false;
	}

	bool Collision::CheckCircleCircle(
		CircleCollider* lhs,
		CircleCollider* rhs)
	{
		Vector3 lhsPos = lhs->GetWorldPosition();
		Vector3 rhsPos = rhs->GetWorldPosition();

		float dx = lhsPos.x - rhsPos.x;
		float dy = lhsPos.y - rhsPos.y;

		float radiusSum = lhs->GetRadius() + rhs->GetRadius();

		return dx * dx + dy * dy <= radiusSum * radiusSum;
	}

	bool Collision::CheckBoxBox(
		BoxCollider* lhs,
		BoxCollider* rhs)
	{
		Vector3 lhsPos = lhs->GetWorldPosition();
		Vector3 rhsPos = rhs->GetWorldPosition();

		Vector2 lhsSize = lhs->GetSize();
		Vector2 rhsSize = rhs->GetSize();

		float lhsHalfX = lhsSize.x * 0.5f;
		float lhsHalfY = lhsSize.y * 0.5f;
		float rhsHalfX = rhsSize.x * 0.5f;
		float rhsHalfY = rhsSize.y * 0.5f;

		return std::abs(lhsPos.x - rhsPos.x) <= lhsHalfX + rhsHalfX &&
			std::abs(lhsPos.y - rhsPos.y) <= lhsHalfY + rhsHalfY;
	}

	bool Collision::CheckCircleBox(
		CircleCollider* circle,
		BoxCollider* box)
	{
		Vector3 circlePos = circle->GetWorldPosition();
		Vector3 boxPos = box->GetWorldPosition();
		Vector2 boxSize = box->GetSize();

		float halfX = boxSize.x * 0.5f;
		float halfY = boxSize.y * 0.5f;

		float closestX = fClamp(
			circlePos.x,
			boxPos.x - halfX,
			boxPos.x + halfX
		);

		float closestY = fClamp(
			circlePos.y,
			boxPos.y - halfY,
			boxPos.y + halfY
		);

		float dx = circlePos.x - closestX;
		float dy = circlePos.y - closestY;

		float radius = circle->GetRadius();

		return dx * dx + dy * dy <= radius * radius;
	}
}