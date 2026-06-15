#include "GameManagerPrefab.h"

#include "Engine/Object/GameObject.h"

#include "Game/Scripts/GameManager/GameManager.h"

namespace Bisang
{
    std::unique_ptr<GameObject> GameManagerPrefab::Instantiate()
    {
        std::unique_ptr<GameObject> gm = std::make_unique<GameObject>();
        gm->SetName("GameManager");

        gm->AddComponent<GameManager>();

        return gm;
    }
}
