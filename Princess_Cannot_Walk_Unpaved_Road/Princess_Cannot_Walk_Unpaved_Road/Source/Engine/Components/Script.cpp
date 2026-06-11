#include "Script.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Scene/Scene.h"

namespace Bisang
{
	GameObject* Script::Instantiate(const std::string& prefabName) const
	{
		return m_ownerObj->GetScene()->Instantiate(prefabName);
	}

	GameObject* Script::FindGameObjectByName(const std::string& name) const
	{
		return m_ownerObj->GetScene()->FindGameObjectByName(name);
	}

	InputManager* Script::GetInputManager() const
	{
		return m_ownerObj->GetScene()->GetInputManager();
	}
}