#pragma once

namespace Bisang
{
    class GameObject;
    class Scene;

    class IPrefab
    {
    public:
        virtual ~IPrefab() = default;
        virtual GameObject* Instantiate(Scene* scene) = 0;
    };
}
