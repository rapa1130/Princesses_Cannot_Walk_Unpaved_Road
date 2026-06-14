#include "Game/Prefabs/PlayerPrefab.h"

#include "Engine/Core/Layer.h"
#include "Engine/Resource/ResourceManager.h"

#include "Engine/Components/Transform.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Components/Collider/BoxCollider.h"
#include "Engine/Components/Animation/Animator.h"

#include "Game/Scripts/Player/PlayerController.h"
#include "Game/Scripts/Player/PlayerAnimationController.h"
#include "Game/Scripts/Player/PlayerStatus.h"
#include "Game/Scripts/Player/PickUpObject.h"

#include <iostream>

namespace Bisang
{
    std::unique_ptr<GameObject> PlayerPrefab::Instantiate()
    {
        std::unique_ptr<GameObject> player = std::make_unique<GameObject>();
        player->SetName("Player");

        auto* tf = player->GetComponent<Transform>();
        tf->SetScale({ 0.7f, 0.7f });
        tf->SetPosition({ 400, 400, 1 });

        auto* sr = player->AddComponent<SpriteRenderer>();
        sr->SetLayer(Layer::Iso);
        sr->SetSprite(m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Default/Player_Front.png"));

        auto* bc = player->AddComponent<BoxCollider>();
        bc->SetSize({ 10.0f,21.0f });

        auto* animator = player->AddComponent<Animator>();

        player->AddComponent<PlayerController>();
        player->AddComponent<PlayerAnimationController>();
        player->AddComponent<PlayerStatus>();

        return player;
    }

    std::unique_ptr<GameObject> PickUpObjPrefab::Instantiate()
    {
        std::unique_ptr<GameObject> pickUpObj = std::make_unique<GameObject>();
        pickUpObj->SetName("PickUpObj");

        auto* tf = pickUpObj->GetComponent<Transform>();
        tf->SetPosition({ -5, -45, 1 });
        tf->SetScale({ 0.5, 0.5 });

        auto* sr = pickUpObj->AddComponent<SpriteRenderer>();
        sr->SetLayer(Layer::Iso);

        pickUpObj->AddComponent<PickUpObject>();
#
        return pickUpObj;
    }
}