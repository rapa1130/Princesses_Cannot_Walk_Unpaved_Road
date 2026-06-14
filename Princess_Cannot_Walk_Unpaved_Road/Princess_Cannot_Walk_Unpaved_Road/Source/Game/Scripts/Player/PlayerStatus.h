#pragma once
#include "Engine/Components/Script.h"

#include "Game/Scripts/Blocks/BlockObjectInfo.h"

#include <memory>

namespace Bisang
{
	class TextureResource;

	class PlayerStatus : public Script
	{
	public:
		PlayerStatus(GameObject* ownerObj) : Script(ownerObj) {}

		void PickUp(BlockId bObj)
		{
			m_heldBlockObj = bObj;
		}

		void PutDown()
		{
			m_heldBlockObj = BlockId::Empty;
		}

		BlockId GetHeldBlockObj() { return m_heldBlockObj; }

	private:
		BlockId m_heldBlockObj = BlockId::Empty;
	};
}
