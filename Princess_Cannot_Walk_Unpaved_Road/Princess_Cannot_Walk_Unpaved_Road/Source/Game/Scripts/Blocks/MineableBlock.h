#pragma once
#include "Engine/Components/BlockMap/Block.h"

namespace Bisang
{
	class MineableBlock : public Block
	{
	public:
		void OnMined(int dmg)
		{
			m_currentHp -= dmg;
			if (m_currentHp <= 0)
			{
				Break();
			}
		}

		virtual void Break() = 0;

	private:
		int m_maxHp;
		int m_currentHp;
	};
}