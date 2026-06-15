#pragma once
#include "Engine/Prefab/Prefab.h"
#include "Engine/Object/GameObject.h"

namespace Bisang
{

    class CameraPrefab : public IPrefab
    {
    public:
        CameraPrefab(ResourceManager* rm)
            : IPrefab(rm)
        {
        }

        std::unique_ptr<GameObject> Instantiate() override;
    };
}