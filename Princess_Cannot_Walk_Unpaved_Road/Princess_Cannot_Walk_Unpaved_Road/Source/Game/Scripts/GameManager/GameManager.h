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
    class MonsterController;
    class AudioManager;

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
        void SpawnPortal();

    private:
        BlockMap* m_blockMap = nullptr;
        AudioManager* m_audio = nullptr;

        int m_playerZ = 1;   // ÇÃ·¹ÀÌ¾î ºí·°¸Ê ³ôÀÌ
        Int3 m_startPosition;
        Int3 m_endPosition;

        Transform* m_player1 = nullptr;
        Transform* m_player2 = nullptr;
        Transform* m_princess = nullptr;
        MonsterController* m_rabbit = nullptr;
        GameObject* m_highlighter = nullptr;    
        GameObject* m_playerGO = nullptr;

    };
}