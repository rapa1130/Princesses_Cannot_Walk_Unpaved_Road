#include "Game/Prefabs/TitlePrefab.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Core/Layer.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/TextRenderer.h"

#include "Game/Scripts/SceneChange/MainSceneChange.h"
#include "Game/Scripts/SceneChange/StorySceneChange.h"
#include "Game/Scripts/Text/TextEffect.h"

namespace Bisang
{
    std::unique_ptr<GameObject> TitlePrefab::Instantiate()
    {
        std::unique_ptr<GameObject> title = std::make_unique<GameObject>();

        Transform* transform = title->GetComponent<Transform>();
        transform->SetPosition({ 400, 60, 0 });
        transform->SetScale({ 0.5f, 0.5f });

        title->AddComponent<MainSceneChange>();

        return title;
    }

    std::unique_ptr<GameObject> TitleTextPrefab::Instantiate()
    {
        std::unique_ptr<GameObject> titleText = std::make_unique<GameObject>();

        Transform* transform = titleText->GetComponent<Transform>();
        transform->SetPosition({ 650, 670, 0 });
        transform->SetScale({ 1000, 1 });

        TextRenderer* text = titleText->AddComponent<TextRenderer>();
        text->SetLayer(Layer::UI);
        text->SetTextFormat(m_resourceManager->LoadTextFormat(L"맑은 고딕", 25));
        text->SetText(L"게임을 시작하려면 스페이바를 눌러주세요.");
        text->SetColor(Color::White);
        text->SetWidth(1000);

        titleText->AddComponent<TextEffect>();

        return titleText;
    }

    std::unique_ptr<GameObject> CarToonPrefab::Instantiate()
    {
        std::unique_ptr<GameObject> cartoon = std::make_unique<GameObject>();

        Transform* transform = cartoon->GetComponent<Transform>();
        transform->SetPosition({ -400, -485, 0 });
        transform->SetScale({ 0.73, 0.73 });

        SpriteRenderer* sprite = cartoon->AddComponent<SpriteRenderer>();
        sprite->SetSprite(m_resourceManager->LoadTexture(L"Assets/Textures/Cartoon/Cartoon.png"));

        cartoon->AddComponent<StorySceneChange>();

        return cartoon;
    }

}