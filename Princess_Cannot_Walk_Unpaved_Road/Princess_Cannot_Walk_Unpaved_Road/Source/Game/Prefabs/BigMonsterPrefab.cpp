#include "BigMonsterPrefab.h"
#include "Game/Scripts/Monster/MonsterController.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	std::unique_ptr<GameObject> BigMonsterPrefab::Instantiate()
	{
		std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
		obj->SetName("BigMonster");
		obj->AddComponent<MonsterController>();

		auto* sr= obj->AddComponent<SpriteRenderer>();
		sr->SetSprite(m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Monsters/Rabbit Monster.png"));

		return obj;
	}
}