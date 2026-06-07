#include "BlockMap.h"
#include "Engine/Math/Degree.h"
#include <cassert>
#include <cmath>

namespace Bisang
{
    BlockMap::BlockMap(GameObject* ownerObj, Scene* scene)
        : Component(ownerObj, scene)
    {
        SetAngle(45.0f, 35.264f);
    }

    void BlockMap::InitMap(int width, int height, int depth)
    {
        assert(width > 0);
        assert(height > 0);
        assert(depth > 0);

        m_width = width;
        m_height = height;
        m_depth = depth;

        m_map.assign(
            m_width * m_height * m_depth,
            Block{}
        );
    }

    void BlockMap::SetBlockSize(float width, float height, float depth)
    {
        assert(width > 0.f);
        assert(height > 0.f);
        assert(depth > 0.f);

        m_blockWidth = width;
        m_blockHeight = height;
        m_blockDepth = depth;
    }

    int BlockMap::Index(Int3 pos) const
    {
        // 블럭인덱스를 1차원 인덱스로 변환
        return pos.z * (m_width * m_depth)
            + pos.y * m_width
            + pos.x;
    }

    bool BlockMap::InBounds(Int3 pos) const
    {
        return pos.x >= 0 &&
            pos.y >= 0 &&
            pos.z >= 0 &&
            pos.x < m_width &&
            pos.y < m_depth &&
            pos.z < m_height;
    }

    const Block* BlockMap::GetBlock(Int3 pos) const
    {
        if (!InBounds(pos))
            return nullptr;

        return &m_map[Index(pos)];
    }

    Block* BlockMap::GetBlock(Int3 pos)
    {
        if (!InBounds(pos))
            return nullptr;

        return &m_map[Index(pos)];
    }

    void BlockMap::SetBlock(Int3 pos, BlockId id)
    {
        if (!InBounds(pos))
            return;

        Block& block = m_map[Index(pos)];
        block.blockId = id;
    }

    void BlockMap::RemoveBlock(Int3 pos)
    {
        if (!InBounds(pos))
            return;

        Block& block = m_map[Index(pos)];
        block.blockId = BlockId::Empty;
    }

    bool BlockMap::IsEmpty(Int3 pos) const
    {
        const Block* block = GetBlock(pos);

        if (block == nullptr)
            return true;

        return block->blockId == BlockId::Empty;
    }

    Vector2 BlockMap::BlockToWorld(Int3 pos) const
    {
        return
            m_axisX * (static_cast<float>(pos.x) * m_blockWidth) +
            m_axisY * (static_cast<float>(pos.y) * m_blockDepth) +
            m_axisZ * (static_cast<float>(pos.z) * m_blockHeight);
    }

    Int3 BlockMap::WorldToBlock(Vector2 worldPos, int heightLayer) const
    {
        Vector2 adjustedWorld =
            worldPos -
            m_axisZ * (static_cast<float>(heightLayer) * m_blockHeight);

        float ax = m_axisX.x * m_blockWidth;
        float ay = m_axisX.y * m_blockWidth;

        float bx = m_axisY.x * m_blockDepth;
        float by = m_axisY.y * m_blockDepth;

        float det = ax * by - ay * bx;

        assert(std::abs(det) > 0.00001f);

        float fx =
            (adjustedWorld.x * by -
                adjustedWorld.y * bx) / det;

        float fy =
            (ax * adjustedWorld.y -
                ay * adjustedWorld.x) / det;

        Int3 result;
        result.x = static_cast<int>(std::floor(fx));
        result.y = static_cast<int>(std::floor(fy));
        result.z = heightLayer;

        return result;
    }

    void BlockMap::SetAngle(float yaw, float pitch)
    {
        m_yaw = yaw;
        m_pitch = pitch;

        float yawRad = DegToRad(yaw);
        float pitchRad = DegToRad(pitch);

        m_axisX =
        {
            cosf(yawRad),
            sinf(yawRad) * sinf(pitchRad)
        };

        m_axisY =
        {
           -cosf(yawRad),
            sinf(yawRad) * sinf(pitchRad)
        };

        m_axisZ =
        {
            0.f,
           -cosf(pitchRad)
        };
    }
}