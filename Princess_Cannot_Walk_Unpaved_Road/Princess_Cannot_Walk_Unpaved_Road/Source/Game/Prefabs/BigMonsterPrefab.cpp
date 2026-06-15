#include "BigMonsterPrefab.h"
#include "Game/Scripts/Monster/MonsterController.h"

namespace Bisang
{
	std::unique_ptr<GameObject> BigMonsterPrefab::Instantiate()
	{
		std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
		obj->SetName("BigMonster");
		obj->AddComponent<MonsterController>();
	}
}