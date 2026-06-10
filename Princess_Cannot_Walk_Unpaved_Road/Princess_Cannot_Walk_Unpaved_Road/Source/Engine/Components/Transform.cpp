#include "Transform.h"
#include "Engine/Object/GameObject.h"
#include"Engine/Components/Component.h"
namespace Bisang
{
    Transform::Transform(GameObject* ownerObj) :
        Component(ownerObj)
    {
    }
    Vector3 Transform::GetWorldPosition()
    {
        // 부모가 없으면 현재 위치가 월드 위치
        if (nullptr == m_ownerObj->GetParent())
        {
            return m_pos;
        }

        // 부모의 월드 위치에 자신의 로컬 위치를 더해서 월드 위치를 계산
        return m_ownerObj
            ->GetParent()
            ->GetComponent<Transform>()
            ->GetWorldPosition()
            + m_pos;
    }
}