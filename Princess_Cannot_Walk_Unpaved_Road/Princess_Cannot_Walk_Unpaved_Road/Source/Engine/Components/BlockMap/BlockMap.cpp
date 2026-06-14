#include "BlockMap.h"
#include "Engine/Math/Degree.h"
#include "Engine/Math/Vector.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include <cassert>
#include <cmath>
#include <map>

namespace Bisang
{
    BlockMap::BlockMap(GameObject* ownerObj)
        : Component(ownerObj)
    {
        SetAngle(81.489f, 6.44086f, 210.3719f);
        m_blockWidth = 239.641f;
        m_blockHeight = 58.1892f;
        m_blockDepth = 417.479f;

    }

    void BlockMap::InitMap(int width, int height, int depth)
    {
        assert(width > 0);
        assert(height > 0);
        assert(depth > 0);

        m_width = width;
        m_height = height;
        m_depth = depth;

        m_map.assign(m_width * m_height * m_depth, -1);
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

    int BlockMap::Index(const Int3& pos) const
    {
        return pos.z * (m_width * m_depth)
            + pos.y * m_width
            + pos.x;
    }

    bool BlockMap::InBounds(const Int3& pos) const
    {
        return pos.x >= 0 &&
            pos.y >= 0 &&
            pos.z >= 0 &&
            pos.x < m_width &&
            pos.y < m_depth &&
            pos.z < m_height;
    }

    int BlockMap::GetBlock(const Int3& pos)
    {
        if (!InBounds(pos))
            return -1;

        return m_map[Index(pos)];
    }

    void BlockMap::SetBlock(const Int3& pos, int blockId)
    {
        if (!InBounds(pos))
            return;

        m_map[Index(pos)] = blockId;
    }

    void BlockMap::RemoveBlock(const Int3& pos)
    {
        if (!InBounds(pos))
            return;

        int index = Index(pos);
        m_map[index] = -1;
    }

    bool BlockMap::IsEmpty(const Int3& pos)
    {
        if (GetBlock(pos) == -1)
        {
            return true;
        }
        
        return false;
    }

    Vector3 BlockMap::BlockToWorld(const Int3& pos) const
    {
        Vector2 local2D =
            m_axisX * (static_cast<float>(pos.x) * m_blockWidth) +
            m_axisY * (static_cast<float>(pos.y) * m_blockDepth) +
            (m_axisZ * -1.0f) * (static_cast<float>(pos.z) * m_blockHeight);

        Transform* transform = m_ownerObj->GetComponent<Transform>();

        Vector3 origin = transform->GetWorldPosition();
        Vector2 scale  = transform->GetScale();

        return Vector3(
            origin.x + local2D.x * scale.x,
            origin.y + local2D.y * scale.y,
            static_cast<float>(pos.z)
        );
    }

    bool BlockMap::WorldToBlock(const Vector3& worldPos, Int3& outPos, int heightLayer) const
    {
        // 블록맵의 Transform 정보
        Transform* transform = m_ownerObj->GetComponent<Transform>();

        // 블록맵 원점 위치
        Vector2 offset = (m_axisX * (m_blockWidth / 2 * transform->GetScale().x)) + (m_axisY * (m_blockDepth / 2 * transform->GetScale().y));
        Vector3 origin = transform->GetWorldPosition() - offset;

        // 블록맵 스케일
        Vector3 scale = transform->GetScale();

        // 월드 좌표 -> 블록맵 로컬 좌표 변환
        // BlockToWorld()에서 적용한
        // local * scale + origin
        Vector2 world2D(
            (worldPos.x - origin.x) / scale.x,
            (worldPos.y - origin.y) / scale.y
        );

        // 선택한 높이층(z)의 영향을 제거
        // BlockToWorld()에서
        // (-m_axisZ * height)
        // 를 적용했으므로 역변환에서는 더해줌
        Vector2 adjustedWorld =
            world2D +
            m_axisZ * (static_cast<float>(heightLayer) * m_blockHeight);

        // 블록 X축 한 칸 이동 시 월드 이동량
        float ax = m_axisX.x * m_blockWidth;
        float ay = m_axisX.y * m_blockWidth;

        // 블록 Y축 한 칸 이동 시 월드 이동량
        float bx = m_axisY.x * m_blockDepth;
        float by = m_axisY.y * m_blockDepth;

        // 2x2 기저 행렬 determinant
        // 역행렬 계산에 사용
        float det = ax * by - ay * bx;

        // 두 축이 평행하면 역변환 불가능
        assert(std::abs(det) > 0.00001f);

        // 역행렬을 이용하여 블록 X 좌표 계산
        float fx =
            (adjustedWorld.x * by -
                adjustedWorld.y * bx) / det;

        // 역행렬을 이용하여 블록 Y 좌표 계산
        float fy =
            (ax * adjustedWorld.y -
                ay * adjustedWorld.x) / det;

        Int3 result;

        // 소수점 이하를 버려 해당 블록 셀 인덱스로 변환
        result.x = static_cast<int>(std::floor(fx));
        result.y = static_cast<int>(std::floor(fy));
        result.z = heightLayer;

        // 맵 범위를 벗어난 경우 실패
        if (!InBounds(result))
            return false;

        // 결과 반환
        outPos = result;
        return true;
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
    }
}