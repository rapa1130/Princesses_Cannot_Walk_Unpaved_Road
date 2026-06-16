#pragma once

#include "Engine/Components/Script.h"
#include "Engine/Math/Int3.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 2
#define MAP_DEPTH 100

namespace Bisang
{
    class GameObject;
    class BlockMap;

    class GameManager : public Script
    {
    public:
        GameManager(GameObject* ownerObj) : Script(ownerObj) {}

        void Start() override;
        void Update(float dT) override;

        Int3 GetStartRailPosition() { return Int3(m_startPosition.x, 0, m_playerZ); }

    private:
        unsigned int CreateRandomSeed() const;
        void GenerateMap();
        void SpawnPlayer1();
        void SpawnPlayer2();
        void SpawnPrincess();
        void SpawnRabbit();
        void SetCameraPrincess();

    private:
        BlockMap* m_blockMap = nullptr;
        int m_playerZ = 1;   // 플레이어 블럭맵 높이
        Int3 m_startPosition;
        Int3 m_endPosition;

        Transform* m_player1 = nullptr;
        Transform* m_player2 = nullptr;
        Transform* m_princess = nullptr;
        Transform* m_rabbit = nullptr;
    };
}