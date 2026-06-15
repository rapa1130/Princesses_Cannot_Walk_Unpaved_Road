#include "BuildingRoad.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Math/Int3.h"
#include "Engine/Math/Vector.h"
#include "Engine/Input/InputManager.h"

#include "Game/Scripts/Player/PlayerStatus.h"
#include "Game/Scripts/Player/PlayerController.h"
#include "Game/Scripts/Blocks/BlockInfoProvider.h"

#include <iostream>

namespace Bisang
{
	void BuildingRoad::Start()
	{
		m_playerStatus = m_ownerObj->GetComponent<PlayerStatus>();

		m_blockMap =
			FindGameObjectByName("BlockMap")
			->GetComponent<BlockMap>();
		m_controller = m_ownerObj->GetComponent<PlayerController>();

		BlockObjectInfoProvider* provider =
			FindGameObjectByName("BlockMap")
			->GetComponent<BlockObjectInfoProvider>();

		m_infoTable = provider->GetTable();
	}

	void BuildingRoad::Update(float dT)
	{
		Int3 currentPos = m_controller->GetCurrentPos();
		Int3 BelowPos = currentPos - Int3{0, 0, -1};

		int id = m_blockMap->GetBlock(currentPos);
		BlockObjectInfo info = m_infoTable->Get(static_cast<BlockId>(id));

		BlockId heldBlockObj = m_playerStatus->GetHeldBlockObj();
		BlockObjectInfo heldInfo = m_infoTable->Get(heldBlockObj);

		if (info.id == BlockId::ClayResource &&
			heldInfo.toolType == ToolType::Hammer)
		{
			if (m_buildingTimer >= m_buiildingTime)
			{
				m_blockMap->SetBlock(currentPos, (int)(BlockId::RailPath));
			}

			m_buildingTimer += dT;
		}

		else
		{
			m_buildingTimer = 0.f;
		}



	}
}