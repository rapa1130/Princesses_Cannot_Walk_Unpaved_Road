#pragma once

namespace Bisang
{
    class ResourceManager;
    class InputManager;
    class PrefabFactory;

    struct GameContext
    {
        ResourceManager* resourceManager = nullptr;
        InputManager* inputManager = nullptr;
        PrefabFactory* prefabFactory = nullptr;
    };
}