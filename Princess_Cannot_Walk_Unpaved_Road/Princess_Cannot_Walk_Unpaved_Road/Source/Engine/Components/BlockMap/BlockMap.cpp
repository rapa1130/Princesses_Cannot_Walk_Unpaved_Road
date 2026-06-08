#include "BlockMap.h"
#include "Engine/Math/Degree.h"
#include "Engine/Math/Vector.h"
#include <cassert>
#include <cmath>

namespace Bisang
{
    BlockMap::BlockMap(GameObject* ownerObj, Scene* scene)
        : Component(ownerObj, scene)
    {
        //SetAngle(45.0f, 35.264f,10.0f);
        //m_yaw = 81.489f;
        //m_pitch = 6.44086f;
        //m_theta = 30.3719f;
        SetAngle(81.489f, 6.44086f, 210.3719f);
        m_blockWidth = 125.49f;
        m_blockHeight= 60.0f;
        m_blockDepth = 212.91f;
        
    }

    void BlockMap::InitMap(int width, int height, int depth)
    {
        assert(width > 0);
        assert(height > 0);
        assert(depth > 0);

        m_width = width;
        m_height = height;
        m_depth = depth;

        m_map.assign(m_width * m_height * m_depth, Block{});
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

        m_map[Index(pos)].blockId = id;
    }

    void BlockMap::RemoveBlock(Int3 pos)
    {
        if (!InBounds(pos))
            return;

        m_map[Index(pos)].blockId = BlockId::Empty;
    }

    bool BlockMap::IsEmpty(Int3 pos) const
    {
        const Block* block = GetBlock(pos);

        if (block == nullptr)
            return true;

        return block->blockId == BlockId::Empty;
    }

    Vector3 BlockMap::BlockToWorld(Int3 pos) const
    {
        Vector2 world2D =
            m_axisX * (static_cast<float>(pos.x) * m_blockWidth) +
            m_axisY * (static_cast<float>(pos.y) * m_blockDepth) +
            m_axisZ * (static_cast<float>(pos.z) * m_blockHeight);

        return Vector3(
            world2D.x,
            world2D.y,
            static_cast<float>(pos.z) * m_blockHeight
        );
    }

    Int3 BlockMap::WorldToBlock(Vector3 worldPos, int heightLayer) const
    {
        Vector2 world2D(
            worldPos.x,
            worldPos.y
        );

        Vector2 adjustedWorld =
            world2D -
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

    void BlockMap::SetAngle(float yaw, float pitch,float theta)
    {
        m_yaw = yaw;
        m_pitch = pitch;
        m_theta = theta;

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
           cosf(pitchRad)
        };
        
        m_axisX = Vector2::Rotate2D(m_axisX, DegToRad(m_theta));
        m_axisY = Vector2::Rotate2D(m_axisY, DegToRad(m_theta));
        m_axisZ = Vector2::Rotate2D(m_axisZ, DegToRad(m_theta));
        
    }
}