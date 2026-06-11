#include "GameRegistry.h"

#include "Engine/Scene/SceneManager.h"
#include "Engine/Prefab/PrefabFactory.h"

#include "Game/Scenes/SampleScene.h"
#include "Game/Scenes/BlockMapTestScene.h"
#include "Game/Prefabs/PlayerPrefab.h"
#include "Game/Prefabs/BlockMapPrefab.h"
#include "Game/Prefabs/DebugOverlay.h"

namespace Bisang
{
    void GameRegistry::RegisterScenes(SceneManager* sceneManager)
    {
        sceneManager->AddScene<SampleScene>("SampleScene");
        sceneManager->AddScene<BlockMapTestScene>("BlockMapTestScene");
        sceneManager->SetStartScene("BlockMapTestScene");
    }

    void GameRegistry::RegisterPrefabs(PrefabFactory* prefabFactory)
    {
        prefabFactory->RegisterPrefab<PlayerPrefab>("Player");
        prefabFactory->RegisterPrefab<BlockMapPrefab>("BlockMap");
        prefabFactory->RegisterPrefab<DebugOverlay>("DebugOverlay");
    }
}