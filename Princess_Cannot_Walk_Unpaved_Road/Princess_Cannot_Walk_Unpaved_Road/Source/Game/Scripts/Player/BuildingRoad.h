#pragma once
#include "Engine/Components/Script.h"
namespace Bisang
{
	class PlayerStatus;
	class BlockMap;
	class PlayerController;
	class BlockObjectInfoTable;
	class InputManager;
	class AudioManager;

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
		AudioManager* m_audio = nullptr;


		float m_buildingTimer = 0.f;
		float m_buiildingTime = 0.5f;
		float m_buildingTimer2 = 0.f;
		float m_buiildingTime2 = 0.5f;


		float m_soundTimer = 0.f;
		float m_soundInterval = 0.25f;
	};


}