#pragma once
#include "Engine/Components/Script.h"
namespace Bisang
{
	class PlayerStatus;
	class BlockMap;
	class PlayerController;
	class BlockObjectInfoTable;
	class InputManager;

	class BuildingRoad : public Script
	{
	public:
		BuildingRoad(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;

	private:
		PlayerStatus* m_playerStatus = nullptr;
		BlockMap* m_blockMap = nullptr;
		PlayerController* m_controller = nullptr;
		BlockObjectInfoTable* m_infoTable = nullptr;


		float m_buildingTimer = 0.f;
		float m_buiildingTime = 0.5f;
	};


}