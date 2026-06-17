#include "Game/Prefabs/TitlePrefab.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Core/Layer.h"

#include "Game/Scripts/SceneChange/MainSceneChange.h"

namespace Bisang
{
    std::unique_ptr<GameObject> TitlePrefab::Instantiate()
    {
        std::unique_ptr<GameObject> title = std::make_unique<GameObject>();

        Transform* transform = title->GetComponent<Transform>();
        transform->SetPosition({ 400, 400, 0 });

        title->AddComponent<MainSceneChange>();

        return title;
    }
}