#pragma once

namespace Bisang
{
	class Collider;
	class BoxCollider;
	class CircleCollider;

	class Collision
	{
	public:
		static bool Check(Collider* lhs, Collider* rhs);

	private:
		static bool CheckCircleCircle(
			CircleCollider* lhs,
			CircleCollider* rhs);

		static bool CheckBoxBox(
			BoxCollider* lhs,
			BoxCollider* rhs);

		static bool CheckCircleBox(
			CircleCollider* circle,
			BoxCollider* box);
	};
}