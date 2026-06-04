#include "GameObject.h"

namespace Bisang
{
	GameObject::GameObject(Scene* scene) : m_scene(scene)
	{
		// 게임 오브젝트는 트랜스폼 필수 보유
		// AddComponent<Transform>();
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

		// 소유중인 랜더러블 컴포넌트 씬에 등록 해제
		for (RenderableComponent* rComp : m_renderableComponents)
		{
			m_scene->RemoveRenderableComponent(rComp);
		}
	}
}