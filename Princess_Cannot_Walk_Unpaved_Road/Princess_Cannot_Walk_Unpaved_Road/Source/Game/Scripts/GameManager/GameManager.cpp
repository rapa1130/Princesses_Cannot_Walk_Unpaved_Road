         #include "GameManager.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/BlockMap/BlockMapRenderer.h"
#include "Engine/Components/Camera/CameraController.h"
#include "Engine/Components/Transform.h"

#include "Game/Scripts/Blocks/BlockInfoProvider.h"
#include "Game/Scripts/Map/BlockMapGenerator.h"
#include "Game/Scripts/Map/RailManager.h"
#include "Game/Scripts/Player/PlayerController.h"
#include "Game/Scripts/Highlighter/Highlighter.h"

#include <random>
#include <iostream>

namespace Bisang
{
	void GameManager::Start()
	{
		m_blockMap = FindGameObjectByName("BlockMap")->GetComponent<BlockMap>();

		// 시작, 끝 지점 초기화
		m_startPosition = { MAP_WIDTH / 2, 10 , m_playerZ };
		m_endPosition = { MAP_WIDTH / 2, 30 , m_playerZ };

		// 랜덤 맵 생성
		GenerateMap();
		
		FindGameObjectByName("RailTracker")->GetComponent<RailManager>()->FindInitialPath();

		// 플레이어 스폰

		SpawnPlayer1();
		SpawnPlayer2();

		// 공주 스폰
		SpawnPrincess();
		// 토끼 스폰
		SpawnRabbit();

		// 카메라 공주 설정
		SetCameraPrincess();
	}

	void GameManager::Update(float dT)
	{
		Int3 currentPrincessPos;
		if (!m_blockMap->WorldToBlock(m_princess->GetPosition(), currentPrincessPos, 1))
			return;

		if (currentPrincessPos == m_endPosition)
		{
			ChangeScene("BlockMapTestScene");
		}
	}

	void GameManager::GenerateMap()
	{
		unsigned int seed = CreateRandomSeed();   // 시드 생성

		BlockMapGenerator mapGenerator;
		mapGenerator.GenerateProceduralMap(
			m_blockMap,
			seed,
			MAP_WIDTH,
			MAP_HEIGHT,
			MAP_DEPTH,
			m_startPosition,
			m_endPosition);
	}

	unsigned int GameManager::CreateRandomSeed() const
	{
		std::random_device rd;
		return rd();
	}

	void GameManager::SpawnPlayer1()
	{
		Vector3 playerStartPos = m_blockMap->BlockToWorld(m_startPosition);
		GameObject* player1 = Instantiate("Player", playerStartPos + Vector3(0, 0, 0));
		m_player1 = player1->GetComponent<Transform>();

		GameObject* pickUpObj = Instantiate("PickUpObj");
		pickUpObj->SetParent(player1);

		GameObject* highlighter = Instantiate("Highlighter", { 0,0,0 });
		PlayerController* pc = player1->GetComponent<PlayerController>();
		pc->SetHighlight(highlighter->GetComponent<Highlighter>());
	}

	void GameManager::SpawnPlayer2()
	{
		Vector3 playerStartPos = m_blockMap->BlockToWorld(m_startPosition);
		GameObject* player2 = Instantiate("Player", playerStartPos + Vector3(0, -50, 0));
		m_player2 = player2->GetComponent<Transform>();

		m_player2->GetOwner()
			->GetComponent<PlayerController>()
			->SetKeyMapping(
				{ KeyCode::A,
				  KeyCode::D,
				  KeyCode::W,
				  KeyCode::S,
				  KeyCode::Space }
			);

		GameObject* pickUpObj = Instantiate("PickUpObj");
		pickUpObj->SetParent(player2);

		GameObject* highlighter = Instantiate("Highlighter", { 0,0,0 });
		PlayerController* pc = player2->GetComponent<PlayerController>();
		pc->SetHighlight(highlighter->GetComponent<Highlighter>());
	}

	void GameManager::SpawnPrincess()
	{
		Vector3 princessStartPos = m_blockMap->BlockToWorld(Int3(m_startPosition.x, 0, 1));
		m_princess =Instantiate("Princess", princessStartPos)
			->GetComponent<Transform>();
	}

	void GameManager::SetCameraPrincess()
	{
		CameraController* mainCamera =
			FindGameObjectByName("Camera")
			->GetComponent<CameraController>();

		mainCamera->SetTarget(m_princess->GetOwner());
	}

	void GameManager::SpawnRabbit()
	{
		m_rabbit = Instantiate("BigMonster")
			->GetComponent<Transform>();
	}




}