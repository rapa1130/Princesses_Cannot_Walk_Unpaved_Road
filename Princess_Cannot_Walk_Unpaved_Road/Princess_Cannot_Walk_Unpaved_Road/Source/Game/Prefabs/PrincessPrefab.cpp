#include "Game/Prefabs/PrincessPrefab.h"
#include "Game/Scripts/Princess/PrincessController.h"
#include "Game/Scripts/Princess/PrincessAnimationController.h"

#include "Engine/Core/Layer.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/TextRenderer.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Components/Animation/Animator.h"


namespace Bisang
{
	std::unique_ptr<GameObject> PrincessPrefab::Instantiate()
	{
		std::unique_ptr<GameObject> princess = std::make_unique<GameObject>();
        princess->SetName("Princess");

        auto* tf = princess->GetComponent<Transform>();
        tf->SetScale({ 0.85f, 0.85f });

        auto* sr = princess->AddComponent<SpriteRenderer>();
        sr->SetLayer(Layer::Iso);
        sr->SetSprite(m_resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Front.png"));


        princess->AddComponent<Animator>();
        princess->AddComponent<PrincessController>();
        princess->AddComponent<PrincessAnimationController>();

		return princess;
	}
}