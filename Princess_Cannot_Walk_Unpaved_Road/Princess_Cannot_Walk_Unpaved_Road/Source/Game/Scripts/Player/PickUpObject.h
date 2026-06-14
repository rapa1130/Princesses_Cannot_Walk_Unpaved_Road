#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class PlayerStatus;
	class SpriteRenderer;
	class BlockObjectInfoTable;

	class PickUpObject : public Script
	{
	public:
		PickUpObject(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;

	private:
		PlayerStatus* m_playerStatus = nullptr;
		SpriteRenderer* m_pickUpObject = nullptr;
		BlockObjectInfoTable* m_table = nullptr;
	};
}