#include "GameRegistry.h"

#include "Engine/Scene/SceneManager.h"
#include "Engine/Prefab/PrefabFactory.h"

#include "Game/Scenes/SampleScene.h"
#include "Game/Scenes/PlayScene.h"
#include "Game/Scenes/MainScene.h"

#include "Game/Prefabs/PlayerPrefab.h"
#include "Game/Prefabs/BlockMapPrefab.h"
#include "Game/Prefabs/DebugOverlay.h"
#include "Game/Prefabs/PrincessPrefab.h"
#include "Game/Prefabs/CameraPrefab.h"
#include "Game/Prefabs/GameManagerPrefab.h"
#include "Game/Prefabs/BigMonsterPrefab.h"
#include "Game/Prefabs/AudioManagerPrefab.h"
#include "Game/Prefabs/HighlighterPrefab.h"
#include "Game/Prefabs/TitlePrefab.h"
#include "Game/Prefabs/PortalPrefab.h"

namespace Bisang
{
    void GameRegistry::RegisterScenes(SceneManager* sceneManager)
    {
        sceneManager->AddScene<SampleScene>("SampleScene");
        sceneManager->AddScene<PlayScene>("PlayScene");
        sceneManager->AddScene<MainScene>("MainScene");

        sceneManager->SetStartScene("MainScene");
    }

    void GameRegistry::RegisterPrefabs(PrefabFactory* prefabFactory)
    {
        prefabFactory->RegisterPrefab<PlayerPrefab>("Player");
        prefabFactory->RegisterPrefab<PickUpObjPrefab>("PickUpObj");
        prefabFactory->RegisterPrefab<BlockMapPrefab>("BlockMap");
        prefabFactory->RegisterPrefab<DebugOverlay>("DebugOverlay");
        prefabFactory->RegisterPrefab<PrincessPrefab>("Princess");
        prefabFactory->RegisterPrefab<CameraPrefab>("Camera");
        prefabFactory->RegisterPrefab<GameManagerPrefab>("GameManager");
        prefabFactory->RegisterPrefab<BigMonsterPrefab>("BigMonster");
        prefabFactory->RegisterPrefab<AudioManagerPrefab>("AudioManager");
        prefabFactory->RegisterPrefab<HighlighterPrefab>("Highlighter");
        prefabFactory->RegisterPrefab<TitlePrefab>("Title");
        prefabFactory->RegisterPrefab<PortalPrefab>("Portal");
    }
}
