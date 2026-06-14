#include "RailManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"

#include <iostream>
#include <algorithm>

namespace Bisang
{
	void RailManager::Start()
	{
		m_blockMap = m_ownerObj->GetComponent<BlockMap>();
		m_blockMapGen = m_ownerObj->GetComponent<BlockMapGenerator>();
		
		FindInitialPath();

		std::function<void(const int&)> s;
	}

	void RailManager::Update(float dT)
	{
		FindPathFrom(m_railPaths.back());
	}

	void RailManager::FindInitialPath()
	{
		Int3 startRailPos = m_blockMapGen->GetRailStartPosition();
		m_railPaths.push_back(startRailPos);

		FindPathFrom(startRailPos);
	}

	void RailManager::FindPathFrom(const Int3& pos)
	{
		Int3 nowPos = pos;
		while (true)
		{
			Int3 adjacentPos;
			if (false == FindAdjacent(adjacentPos, nowPos)) break;

			m_railPaths.push_back(adjacentPos);
			std::cout <<
				m_railPaths.back().x << ", " <<
				m_railPaths.back().y << ", " <<
				m_railPaths.back().z << ", " <<
				std::endl;
			nowPos = adjacentPos;
		}
	}

	int RailManager::GetNowRailPathSize() const
	{
		return m_railPaths.size();
	}

	const Int3& RailManager::GetRailPathof(int index) const
	{
		return m_railPaths[index];
	}

	bool RailManager::FindAdjacent(Int3& outAdj,const Int3& inPos) const
	{
		for (int i = 0; i < DIRECTION_COUNT; i++)
		{
			Int3 nowDir = { m_findDirX[i], m_findDiry[i], 0 };
			Int3 checkPos = inPos + nowDir;

			if (m_blockMap->GetBlock(checkPos) != static_cast<int>(BlockId::RailPath))
				continue;
			if (IsAlreadyPath(checkPos)) 
				continue;

			outAdj = checkPos;
			return true;
		}
		return false;
	}

	bool RailManager::IsAlreadyPath(const Int3& pos) const
	{
		return m_railPaths.end() != std::find(m_railPaths.begin(), m_railPaths.end(), pos);
	}

}