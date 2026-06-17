#include "BlockInfoProvider.h"
#include "Engine/Components/BlockMap/BlockMapRenderer.h"
#include "Engine/Object/GameObject.h"

namespace Bisang
{
	void BlockObjectInfoProvider::Awake()
	{
		m_table = std::make_unique<BlockObjectInfoTable>();
		m_table->Init(GetResourceManager());
	}

	void BlockObjectInfoProvider::Start()
	{
		BlockMapRenderer* blockMapRenderer = m_ownerObj->GetComponent<BlockMapRenderer>();
		blockMapRenderer->SetBlockObjectInfoTable(m_table.get());
	}
}