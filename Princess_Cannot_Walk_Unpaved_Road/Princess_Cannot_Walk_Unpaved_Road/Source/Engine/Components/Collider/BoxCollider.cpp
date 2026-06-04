#include "BoxCollider.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	Vector2 BoxCollider::GetSize() const
	{
		Vector2 scale = m_transform->GetScale();
		return { m_size.x * scale.x, m_size.y * scale.y };
	}
}