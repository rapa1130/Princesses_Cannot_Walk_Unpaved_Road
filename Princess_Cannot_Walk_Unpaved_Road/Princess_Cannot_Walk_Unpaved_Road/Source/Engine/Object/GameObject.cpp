#include "GameObject.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	GameObject::GameObject()
	{
		// 게임 오브젝트는 트랜스폼 필수 보유
		AddComponent<Transform>();
	}

	GameObject::~GameObject()
	{
		// 부모에서 자식 삭제
		if (m_parent)
		{
			m_parent->RemoveChild(this);   
		}

		// 자식들 삭제
		for (GameObject* child : m_children)   
		{
			child->ClearParent();
			m_scene->DestroyGameObject(child->GetId());
		}
	}
}