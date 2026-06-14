#include "PickUpObject.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/SpriteRenderer.h"

#include "Game/Scripts/Blocks/BlockInfoProvider.h"
#include "Game/Scripts/Player/PlayerStatus.h"

#include <iostream>

namespace Bisang
{
	void PickUpObject::Start()
	{
		m_playerStatus =
			FindGameObjectByName("Player")
			->GetComponent<PlayerStatus>();

		m_pickUpObject =
			m_ownerObj->GetComponent<SpriteRenderer>();

		BlockObjectInfoProvider* provider =
			FindGameObjectByName("BlockMap")
			->GetComponent<BlockObjectInfoProvider>();

		m_table = provider->GetTable();

	}

	void PickUpObject::Update(float dT)
	{
		BlockId id = m_playerStatus->GetHeldBlockObj();
		BlockObjectInfo info = m_table->Get(id);
		m_pickUpObject->SetSprite(info.texture);
	}
}