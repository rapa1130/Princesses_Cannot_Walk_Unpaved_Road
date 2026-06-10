#pragma once
#include <memory>
namespace Bisang
{
    class GameObject;
    class Scene;

    class IPrefab
    {
    public:
        virtual ~IPrefab() = default;
        virtual std::unique_ptr<GameObject> Instantiate() = 0;
    };
}
