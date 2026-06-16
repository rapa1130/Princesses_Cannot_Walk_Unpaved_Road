#pragma once
#include "Engine/Prefab/Prefab.h"
#include "Engine/Object/GameObject.h"

namespace Bisang
{
    class GameManagerPrefab : public  IPrefab
    {
    public:
        GameManagerPrefab(ResourceManager* rm)
            : IPrefab(rm)
        {
        }

        std::unique_ptr<GameObject> Instantiate() override;
    };
}