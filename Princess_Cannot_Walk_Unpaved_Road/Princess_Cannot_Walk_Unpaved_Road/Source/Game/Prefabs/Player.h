#pragma once

#include "Engine/Prefab/Prefab.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Components/Transform.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Core/Layer.h"
#include "Game/Scripts/PlayerController.h"

namespace Bisang
{
    class PlayerPrefab : public IPrefab
    {
    public:
        GameObject* Instantiate(Scene* scene) override
        {
            GameObject* obj = scene->CreateGameObject("Player");

            auto* tf = obj->GetComponent<Transform>();
            tf->SetScale({ 0.2f, 0.2f });

            auto* sr = obj->AddComponent<SpriteRenderer>();
            sr->SetLayer(Layer::Iso);
            sr->SetSprite(L"Assets/Textures/test.png");

            obj->AddComponent<PlayerController>();

            return obj;
        }
    };
}
