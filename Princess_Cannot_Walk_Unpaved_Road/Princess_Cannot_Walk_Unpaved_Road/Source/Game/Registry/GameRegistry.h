#pragma once

namespace Bisang
{
    class SceneManager;
    class PrefabFactory;

    class GameRegistry
    {
    public:
        static void RegisterScenes(SceneManager* sceneManager);
        static void RegisterPrefabs(PrefabFactory* prefabFactory);
    };
}