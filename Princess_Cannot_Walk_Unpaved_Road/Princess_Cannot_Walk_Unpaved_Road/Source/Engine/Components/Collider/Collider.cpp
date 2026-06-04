#include "Collider.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	Collider::Collider(GameObject* ownerObj, Scene* scene, ColliderType type) :
		Component(ownerObj, scene),
		m_type(type),
		m_transform(m_ownerObj->GetComponent<Transform>())
	{
	}

	Vector2 Collider::GetWorldPosition()
	{
		Vector2 pos = m_transform->GetWorldPosition();
		return pos + m_offset;
	}
}