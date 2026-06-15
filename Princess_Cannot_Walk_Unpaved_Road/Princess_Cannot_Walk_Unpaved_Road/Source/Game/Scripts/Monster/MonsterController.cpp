#include "MonsterController.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/Transform.h"

namespace Bisang
{
	void MonsterController::Start()
	{
		GameObject* bObj = FindGameObjectByName("BlockMap");
		m_blockMap = bObj->GetComponent<BlockMap>();
		m_transform = m_ownerObj->GetComponent<Transform>();
	}

	void MonsterController::Update(float dT)
	{

	}
}