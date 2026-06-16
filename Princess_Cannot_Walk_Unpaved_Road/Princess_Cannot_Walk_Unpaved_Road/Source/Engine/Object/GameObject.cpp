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
	}
}