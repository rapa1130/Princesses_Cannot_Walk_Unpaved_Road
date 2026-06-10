#pragma once

#include "Engine/Components/Component.h"
#include "Engine/Math/Vector.h"
#include "Engine/Math/Int3.h"

#include <vector>
#include<map>
namespace Bisang
{

    enum class BlockId
    {
        Empty = 0,
        

        Grass = 1,
        Dirt = 2,
        Water = 3,


        Rock = 4,
        Clay = 5,
        Tree = 6,

        
        OrcTree = 7,

        RailPath = 8,
    };

    struct Block
    {
        BlockId blockId = BlockId::Empty;
    };

    class BlockMap : public Component
    {
    public:
        BlockMap(GameObject* ownerObj, Scene* scene);

    public:
        void InitMap(int width, int height, int depth);
        void SetBlockSize(float width, float height, float depth);
        void GenerateProceduralMap(unsigned int seed);
        void MakeStartZone();

        int Index(Int3 pos) const;
        bool InBounds(Int3 pos) const;

        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }
        int GetDepth() const { return m_depth; }

        float GetBlockWidth() const { return m_blockWidth; }
        float GetBlockHeight() const { return m_blockHeight; }
        float GetBlockDepth() const { return m_blockDepth; }

        const Block* GetBlock(Int3 pos) const;
        Block* GetBlock(Int3 pos);

        void SetBlock(Int3 pos, BlockId id);
        void RemoveBlock(Int3 pos);

        bool IsEmpty(Int3 pos) const;

        Vector3 BlockToWorld(Int3 pos) const;

        // z층을 기준으로 world 좌표를 block 좌표로 변환
        bool WorldToBlock(Vector3 worldPos, Int3& outPos, int heightLayer = 0) const;

        void SetAngle(float yaw, float pitch, float theta);
        Vector2 GetAngle() { return { m_yaw, m_pitch }; }
        float GetTheta() { return m_theta;}

        const Vector2& GetAxisX() const { return m_axisX; }
        const Vector2& GetAxisY() const { return m_axisY; }
        const Vector2& GetAxisZ() const { return m_axisZ; }

        void SetStartPosition(const Int3& pos);
        Int3 GetStartPosition() const;

        bool IsWalkableFloor(BlockId id) const;
        bool IsBlocking(BlockId id) const;

    private:

        /*
                   ______
                  /     /|
                 /_____/ | 
                 |     | |
           높이y |     | /
                 |_____|/  깊이z
                  가로x
        */

        int m_width = 1;   // x축, 가로 블럭 개수
        int m_height = 1;  // z축, 높이 블럭 개수
        int m_depth = 1;   // y축, 깊이 블럭 개수

        float m_blockWidth = 1;   // 화면상 블럭 가로
        float m_blockHeight = 1;  // 화면상 블럭 높이
        float m_blockDepth = 1;   // 화면상 블럭 깊이

        std::vector<Block> m_map;

        float m_yaw = 35.f;     // 좌우 회전
        float m_pitch = 55.f;   // 위아래 기울기
        float m_theta = 10.0f;

        Vector2 m_axisX;
        Vector2 m_axisY;
        Vector2 m_axisZ;

        Int3 m_startPosition;

    };
}