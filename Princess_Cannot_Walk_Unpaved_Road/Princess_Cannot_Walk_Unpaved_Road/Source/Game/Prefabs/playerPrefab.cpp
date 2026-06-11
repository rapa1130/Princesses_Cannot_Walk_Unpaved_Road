#include "Game/Prefabs/PlayerPrefab.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Core/Layer.h"
#include "Game/Scripts/PlayerController.h"
#include "Engine/Resource/ResourceManager.h"
#include <iostream>

namespace Bisang
{
    std::unique_ptr<GameObject> PlayerPrefab::Instantiate()
    {
        std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
        obj->SetName("Player");

        auto* tf = obj->GetComponent<Transform>();
        tf->SetScale({ 0.7f, 0.7f });
        tf->SetPosition({ 400, 400, 1 });

        auto* sr = obj->AddComponent<SpriteRenderer>();
        sr->SetLayer(Layer::Iso);
        sr->SetSprite(m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Front.png"));

        obj->AddComponent<PlayerController>();
        return obj;
    }
}