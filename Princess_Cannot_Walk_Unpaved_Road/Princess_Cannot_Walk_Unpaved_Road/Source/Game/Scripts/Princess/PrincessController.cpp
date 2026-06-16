#include "PrincessController.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/Animation/Animator.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Math/Int3.h"
#include "Engine/Components/Transform.h"

#include "Game/Scripts/Map/BlockMapGenerator.h"
#include "Game/Scripts/Map/RailManager.h"
#include "Game/Scripts/GameManager/GameManager.h"

#include <iostream>

namespace Bisang
{
    void PrincessController::Start()
    {
        GameObject* blockMapGO = FindGameObjectByName("BlockMap");

        m_transform = m_ownerObj->GetComponent<Transform>();
        m_blockMap = blockMapGO->GetComponent<BlockMap>();
        m_railManager = blockMapGO->GetComponent<RailManager>();
    }

    void PrincessController::Update(float dT)
    {
        if (HasReachRoadEnd())
        {
            m_nowMoveDir = Int3{ 0,0,0 };
            return;
        }

        if (!m_railManager->HasRailPathAt(m_nowWalkingRailIndex))
            return;

        const Int3& targetPos = m_railManager->GetRailPathof(m_nowWalkingRailIndex);
        Vector3 targetWorldPos = m_blockMap->BlockToWorld(targetPos);
        Vector3 nowWorldPos = m_transform->GetPosition();

        if (HasReachedCurrentRoadPoint(nowWorldPos, targetWorldPos))
        {
            m_nowWalkingRailIndex++;
            
            if (HasReachRoadEnd()) return;
            if (!m_railManager->HasRailPathAt(m_nowWalkingRailIndex)) return;

            const Int3& nextTargetPos =m_railManager->GetRailPathof(m_nowWalkingRailIndex);

            m_nowMoveDir = nextTargetPos - targetPos;
            return;
        }
        if (m_nowMoveDir == Int3{ 0,0,0 } && m_nowWalkingRailIndex > 0 &&
            m_railManager->HasRailPathAt(m_nowWalkingRailIndex - 1))
        {
            const Int3& prevTargetPos = m_railManager->GetRailPathof(m_nowWalkingRailIndex - 1);
            m_nowMoveDir = targetPos - prevTargetPos;
        }
        Move(nowWorldPos, targetWorldPos, dT);
    }

    float PrincessController::GetMoveSpeed() const
    {
        return m_moveSpeed;
    }

    void PrincessController::SetMoveSpeed(float speed)
    {
        m_moveSpeed = speed;
    }

    Int3 PrincessController::GetMoveDirection() const
    {
        return m_nowMoveDir;
    }


    void PrincessController::Move(const Vector3& nowWorldPos,const Vector3& targetWorldPos, float dT)
    {
        Vector3 dir = (targetWorldPos - nowWorldPos).Normalized();
        Vector3 nextFrmPos = nowWorldPos + dir * m_moveSpeed * dT;
        m_transform->SetPosition(nextFrmPos);
    }
    bool PrincessController::HasReachRoadEnd() const
    {
        if (m_railManager == nullptr)
            return true;

        return m_railManager->GetNowRailPathSize() <= m_nowWalkingRailIndex;
    }
    bool PrincessController::HasReachedCurrentRoadPoint(const Vector3& nowWorldPos, const Vector3& targetWorldPos) const
    {
        float dist = (nowWorldPos - targetWorldPos).Squared();
        float threshold = 1.0f;

        return dist < threshold;
    }
}