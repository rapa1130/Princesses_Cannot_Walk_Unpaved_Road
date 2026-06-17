#pragma once
#include "Engine/Prefab/Prefab.h"
#include "Engine/Object/GameObject.h"

namespace Bisang
{
    class TitlePrefab : public IPrefab
    {
    public:
        TitlePrefab(ResourceManager* rm)
            : IPrefab(rm)
        {
        }

        std::unique_ptr<GameObject> Instantiate() override;
    };
}