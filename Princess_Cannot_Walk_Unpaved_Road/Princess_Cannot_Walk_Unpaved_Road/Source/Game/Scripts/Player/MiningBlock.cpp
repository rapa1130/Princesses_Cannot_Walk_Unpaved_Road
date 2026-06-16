#include "MiningBlock.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Math/Int3.h"
#include "Engine/Math/Vector.h"

#include "Game/Scripts/Player/PlayerStatus.h"
#include "Game/Scripts/Player/PlayerController.h"
#include "Game/Scripts/Blocks/BlockInfoProvider.h"
#include "Game/Scripts/Audio/AudioManager.h"

#include <iostream>

namespace Bisang
{
	void MiningBlock::Start()
	{
		m_playerStatus = m_ownerObj->GetComponent<PlayerStatus>();

		m_blockMap = FindGameObjectByName("BlockMap")
			->GetComponent<BlockMap>();
		m_controller = m_ownerObj->GetComponent<PlayerController>();

		BlockObjectInfoProvider* provider = FindGameObjectByName("BlockMap")
			->GetComponent<BlockObjectInfoProvider>();

		m_infoTable = provider->GetTable();

		m_audio = FindGameObjectByName("AudioManager")
			->GetComponent<AudioManager>();
	}

	void MiningBlock::Update(float dT)
	{
		Int3 currentPos = m_controller->GetCurrentPos();
		Vector2 faceDir = m_controller->GetFaceDir();

		if (faceDir == Vector2{ 1,-1 } ||
			faceDir == Vector2{ -1,-1 } ||
			faceDir == Vector2{ 1,1 } ||
			faceDir == Vector2{ -1,1 })
		{
			return;
		}

		Int3 frontPos = currentPos + Int3(-1 * (int)faceDir.y, (int)faceDir.x, 0);

		int id = m_blockMap->GetBlock(frontPos);
		BlockObjectInfo info = m_infoTable->Get(static_cast<BlockId>(id));

		BlockId heldBlockObj = m_playerStatus->GetHeldBlockObj();
		BlockObjectInfo heldInfo = m_infoTable->Get(heldBlockObj);

		if (info.mineable != nullptr &&
			info.mineable->requiredTool == heldInfo.toolType)
		{
			m_soundTimer += dT;

			if (m_soundTimer >= m_soundInterval)
			{
				if (info.id == BlockId::Clay)
				{
					m_audio->PlayPickAxeSound();
				}

				if (info.id == BlockId::Tree || info.id == BlockId::OrcTree)
				{
					m_audio->PlayAxeSound();
				}
				m_soundTimer = 0.f;
			}

			if (m_miningTimer >= info.mineable->maxHp)
			{
				m_blockMap->SetBlock(frontPos, (int)(info.mineable->dropBlockId));
			}

			m_miningTimer += dT;
		}

		else
		{
			m_miningTimer = 0.f;
			m_soundTimer = 0.f;
		}



	}
}