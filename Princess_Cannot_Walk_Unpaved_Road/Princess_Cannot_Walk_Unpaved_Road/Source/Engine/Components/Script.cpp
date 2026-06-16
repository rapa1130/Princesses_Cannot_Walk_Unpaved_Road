#include "Script.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Scene/Scene.h"

namespace Bisang
{
	GameObject* Script::Instantiate(const std::string& prefabName) const
	{
		return m_ownerObj->GetScene()->Instantiate(prefabName);
	}

	GameObject* Script::Instantiate(const std::string& prefabName, Vector3 worldPos) const
	{
		return m_ownerObj->GetScene()->Instantiate(prefabName, worldPos);
	}

	void Script::Destory(GameObject* obj)
	{
		return m_ownerObj->GetScene()->DestroyGameObject(obj->GetId());
	}

	GameObject* Script::FindGameObjectByName(const std::string& name) const
	{
		return m_ownerObj->GetScene()->FindGameObjectByName(name);
	}

	InputManager* Script::GetInputManager() const
	{
		return m_ownerObj->GetScene()->GetInputManager();
	}

	ResourceManager* Script::GetResourceManager() const
	{
		return m_ownerObj->GetScene()->GetResourceManager();
	}

	void Script::ChangeScene(const std::string& sceneName) const
	{
		m_ownerObj->GetScene()->RequestChangeScene(sceneName);
	}
}