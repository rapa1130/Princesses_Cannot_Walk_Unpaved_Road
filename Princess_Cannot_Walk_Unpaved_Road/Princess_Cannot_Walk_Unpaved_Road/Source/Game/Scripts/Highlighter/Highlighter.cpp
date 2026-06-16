#include "Highlighter.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Components/Transform.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Core/Layer.h"
#include "Game/Scripts/Blocks/BlockInfoProvider.h"
#include "Game/Scripts/Blocks/BlockObjectInfoTable.h"

#include <iostream>

namespace Bisang
{
	void Highlighter::Start()
	{
		m_blockMap = FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();
		m_spriteRenderer = m_ownerObj->GetComponent<SpriteRenderer>();
		m_transform = m_ownerObj->GetComponent<Transform>();
		m_resourceManager = m_ownerObj->GetScene()->GetResourceManager();

		BlockObjectInfoProvider* provider =
			FindGameObjectByName("BlockMap")
			->GetComponent<BlockObjectInfoProvider>();

		m_infoTable = provider->GetTable();

		m_overlayColor = Bisang::Color(1.0f, 1.0f, 1.0f, 0.4f);
		m_spriteRenderer->SetLayer(Layer::Highlight);
		m_spriteRenderer->SetDrawFlags(SpriteDrawFlags::Overlay);
		auto blockMapScale = m_blockMap->GetOwner()->GetComponent<Transform>()->GetScale();
		m_transform->SetScale(blockMapScale);
		m_transform->SetPosition(m_transform->GetPosition() + Vector3(0, 0, 0.01f));
	}

	void Highlighter::Update(float dT)
	{
		if (m_targetBlockID == BlockId::Empty)
		{
			m_spriteRenderer->SetIsVisible(false);
			return;
		}

		m_spriteRenderer->SetIsVisible(true);
		m_spriteRenderer->SetColor(m_overlayColor);

		const BlockObjectInfo* blockInfo = m_infoTable->Find(m_targetBlockID);

		if (blockInfo == nullptr) return;
		m_spriteRenderer->SetSprite(blockInfo->texture);


		Vector3 worldPos = m_blockMap->BlockToWorld(m_targetPosition);
		m_transform->SetPosition(worldPos);
	}

	void Highlighter::SetHighlightBlock(const Int3& blockPos, BlockId blockID)
	{
		m_targetBlockID = blockID;
		m_targetPosition = blockPos;
	}
}