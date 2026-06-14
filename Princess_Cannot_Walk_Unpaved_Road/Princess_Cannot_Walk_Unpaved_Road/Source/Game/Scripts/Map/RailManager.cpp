#include "RailManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"

#include <iostream>
namespace Bisang
{
	void RailManager::Start()
	{
		m_blockMap = m_ownerObj->GetComponent<BlockMap>();
		m_blockMapGen = m_ownerObj->GetComponent<BlockMapGenerator>();
	}

	void RailManager::FindInitialPath()
	{

	}

}