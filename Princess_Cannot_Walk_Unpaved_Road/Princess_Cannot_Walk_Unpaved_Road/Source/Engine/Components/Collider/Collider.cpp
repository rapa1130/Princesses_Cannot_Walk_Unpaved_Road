#include "Collider.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Math/Vector.h"

namespace Bisang
{
	Collider::Collider(GameObject* ownerObj, ColliderType type) :
		Component(ownerObj),
		m_type(type),
		m_transform(m_ownerObj->GetComponent<Transform>())
	{
	}

	Vector3 Collider::GetWorldPosition()
	{
		Vector3 pos = m_transform->GetWorldPosition();
		return pos + m_offset;
	}
}