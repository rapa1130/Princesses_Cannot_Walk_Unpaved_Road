#include "Component.h"
#include"Engine/Components/Transform.h"
#include"Engine/Object/GameObject.h"
#include"Engine/Scene/Scene.h"

namespace Bisang
{
	RenderableComponent::RenderableComponent(GameObject* Owner, Scene* scene)
		: Component(Owner, scene)
	{
		m_transform = m_ownerObj->AddComponent<Transform>();
	}

	ResourceManager* Component::GetResourceManager()
	{ 
		return m_scene->GetResourceManager(); 
	}
}