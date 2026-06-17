#include "GameManagerPrefab.h"

#include "Engine/Object/GameObject.h"

#include "HighlighterPrefab.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Game/Scripts/Highlighter/Highlighter.h"

namespace Bisang
{
    std::unique_ptr<GameObject> HighlighterPrefab::Instantiate()
    {
        std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
        obj->SetName("Highlighter");

        SpriteRenderer* sr = obj->AddComponent<SpriteRenderer>();
        Highlighter* hl = obj->AddComponent<Highlighter>();

        return obj;
    }
}
