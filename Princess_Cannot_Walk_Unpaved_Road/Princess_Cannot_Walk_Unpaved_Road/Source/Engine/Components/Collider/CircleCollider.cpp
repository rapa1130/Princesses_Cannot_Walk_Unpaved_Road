#include "CircleCollider.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	float CircleCollider::GetRadius() const
	{
		Vector2 scale = m_transform->GetScale();
		return m_radius * std::max(scale.x, scale.y);
	}
}