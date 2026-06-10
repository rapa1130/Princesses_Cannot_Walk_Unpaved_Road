#include "Script.h"
#include "Engine/Object/GameObject.h"

namespace Bisang
{
	Script::Script(GameObject* ownerObj) : Component(ownerObj)
	{
		m_scene = m_ownerObj->GetScene();
	}
}