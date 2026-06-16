#include "BuildingRoad.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Math/Int3.h"
#include "Engine/Math/Vector.h"
#include "Engine/Input/InputManager.h"

#include "Game/Scripts/Player/PlayerStatus.h"
#include "Game/Scripts/Player/PlayerController.h"
#include "Game/Scripts/Blocks/BlockInfoProvider.h"
#include "Game/Scripts/Audio/AudioManager.h"

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


		m_audio = FindGameObjectByName("AudioManager")
			->GetComponent<AudioManager>();
	}

	void BuildingRoad::Update(float dT)
	{
		Int3 currentPos = m_controller->GetCurrentPos();
		BlockId heldBlockObj = m_playerStatus->GetHeldBlockObj();
		BlockObjectInfo heldInfo = m_infoTable->Get(heldBlockObj);
		int id;
		BlockObjectInfo info;

		// 돌 길 설치
		Int3 BelowPos = currentPos - Int3{0, 0, -1};
		id = m_blockMap->GetBlock(currentPos);
		info = m_infoTable->Get(static_cast<BlockId>(id));

		if (info.id == BlockId::ClayResource &&
			heldInfo.toolType == ToolType::Hammer)
		{
			m_soundTimer += dT;

			if (m_soundTimer >= m_soundInterval)
			{
				m_audio->PlayHammerSound();
				m_soundTimer = 0.f;
			}

			if (m_buildingTimer >= m_buiildingTime)
			{
				m_blockMap->SetBlock(currentPos, (int)(BlockId::RailPath));
			}

			m_buildingTimer += dT;
		}

		else
		{
			m_buildingTimer = 0.f;
			m_soundTimer = 0.f;
		}


		// 물 판자 설치

		Vector2 faceDir = m_controller->GetFaceDir();
		if (faceDir == Vector2{ 1,-1 } ||
			faceDir == Vector2{ -1,-1 } ||
			faceDir == Vector2{ 1,1 } ||
			faceDir == Vector2{ -1,1 })
		{
			return;
		}
		Int3 frontBelowPos = currentPos + Int3(-1 * (int)faceDir.y, (int)faceDir.x, -1);
		Int3 frontPos = currentPos + Int3(-1 * (int)faceDir.y, (int)faceDir.x, 0);
		id = m_blockMap->GetBlock(frontBelowPos);
		info = m_infoTable->Get(static_cast<BlockId>(id));

		if (info.id == BlockId::Water &&
			heldInfo.id == BlockId::TreeResource)
		{
			if (m_buildingTimer2 >= m_buiildingTime2)
			{
				m_blockMap->SetBlock(frontBelowPos, (int)(BlockId::WoodBridge));
				m_playerStatus->PutDown();

				m_audio->PlayWoodPutSound();
			}

			m_buildingTimer2 += dT;
		}

		else
		{
			m_buildingTimer2 = 0.f;
		}
		
	}
}