#include "RailManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMap.h"

#include "Game/Scripts/GameManager/GameManager.h"

#include <iostream>
#include <algorithm>

namespace Bisang
{
	void RailManager::Start()
	{
		m_blockMap = FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();
		m_gM = FindGameObjectByName("GameManager")->GetComponent<GameManager>();

		std::function<void(const int&)> s;
	}

	void RailManager::Update(float dT)
	{
		if (m_railPaths.empty())
			return;

		FindPathFrom(m_railPaths.back());
	}

	void RailManager::FindInitialPath()
	{
		if (m_blockMap == nullptr)
		{
			m_blockMap = FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();
		}

		if (m_gM == nullptr)
		{
			GameObject* gameManagerObj = FindGameObjectByName("GameManager");
			if (gameManagerObj != nullptr)
			{
				m_gM = gameManagerObj->GetComponent<GameManager>();
			}
		}

		if (m_gM == nullptr || m_blockMap == nullptr)
			return;

		m_railPaths.clear();

		Int3 startRailPos = m_gM->GetStartRailPosition();
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
			nowPos = adjacentPos;
		}
	}

	int RailManager::GetNowRailPathSize() const
	{
		return m_railPaths.size();
	}

	bool RailManager::HasRailPathAt(int index) const
	{
		return index >= 0 && index < static_cast<int>(m_railPaths.size());
	}

	const Int3& RailManager::GetRailPathof(int index) const
	{
		static const Int3 invalidPos{ 0, 0, 0 };
		if (!HasRailPathAt(index))
			return invalidPos;

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