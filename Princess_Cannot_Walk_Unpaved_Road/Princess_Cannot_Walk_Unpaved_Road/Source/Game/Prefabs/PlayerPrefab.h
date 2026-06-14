#pragma once
#include "Engine/Prefab/Prefab.h"
#include "Engine/Object/GameObject.h"

namespace Bisang
{
    class PlayerPrefab : public IPrefab
    {
    public:
        PlayerPrefab(ResourceManager* rm)
            : IPrefab(rm)
        {
        }

        std::unique_ptr<GameObject> Instantiate() override;
    };

    class PickUpObjPrefab : public IPrefab
    {
    public:
        PickUpObjPrefab(ResourceManager* rm)
            : IPrefab(rm)
        {
        }

        std::unique_ptr<GameObject> Instantiate() override;
    };
}