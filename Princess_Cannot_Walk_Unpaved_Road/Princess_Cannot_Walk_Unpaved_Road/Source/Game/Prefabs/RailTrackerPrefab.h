#pragma once
#include "Engine/Prefab/Prefab.h"
#include "Engine/Object/GameObject.h"

namespace Bisang
{
    class RailTrackerPrefab : public IPrefab
    {
    public:
        RailTrackerPrefab(ResourceManager* rm)
            : IPrefab(rm)
        {
        }

        std::unique_ptr<GameObject> Instantiate() override;
    };
}