#pragma once
#include <memory>
namespace Bisang
{
    class GameObject;
    class ResourceManager;

    class IPrefab
    {
    public:
        IPrefab(ResourceManager* rm)
            : m_resourceManager(rm)
        {
        }

        virtual ~IPrefab() = default;
        virtual std::unique_ptr<GameObject> Instantiate() = 0;

    protected:
        ResourceManager* m_resourceManager = nullptr;
    };
}
