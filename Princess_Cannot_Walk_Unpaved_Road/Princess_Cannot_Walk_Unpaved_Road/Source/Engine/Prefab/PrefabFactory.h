#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>
#include <type_traits>

#include "Engine/Prefab/Prefab.h"
#include "Engine/Object/GameObject.h"

namespace Bisang
{
    class PrefabFactory
    {
    public:
        explicit PrefabFactory(ResourceManager* resourceManager)
            : m_resourceManager(resourceManager)
        {
        }

        template <typename T>
        void RegisterPrefab(const std::string& name)
        {
            m_Prefabs[name] = [this]()
                {
                    T prefab(m_resourceManager);
                    return prefab.Instantiate();
                };
        }

        std::unique_ptr<GameObject> Create(const std::string& name)
        {
            auto it = m_Prefabs.find(name);
            if (it == m_Prefabs.end())
                return nullptr;

            return it->second();
        }

    private:
        ResourceManager* m_resourceManager = nullptr;
        std::unordered_map<std::string, std::function<std::unique_ptr<GameObject>()>> m_Prefabs;
    };
}
