#include "Game/Prefabs/BlockMapPrefab.h"

#include "Engine/Components/Transform.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/BlockMap/BlockMapRenderer.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Core/Layer.h"

#include "Game/Scripts/Player/PlayerController.h"
#include "Game/Scripts/Map/BlockMapGenerator.h"
#include "Game/Scripts/Blocks/BlockInfoProvider.h"

#include <random>

namespace Bisang
{
    std::unique_ptr<GameObject> BlockMapPrefab::Instantiate()
    {
        std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
        obj->SetName("BlockMap");

		Transform* bMapT = obj->GetComponent<Transform>();
		bMapT->SetScale({ 0.5, 0.5 });
		bMapT->SetPosition({ 100, 900, 0 });

        BlockMap* bMap = obj->AddComponent<BlockMap>();

		BlockMapRenderer* bMapR = obj->AddComponent<BlockMapRenderer>();
		bMapR->SetLayer(Layer::Iso);
		bMapR->SetBlockMap(bMap);

        obj->AddComponent<BlockObjectInfoProvider>();
        obj->AddComponent<BlockMapGenerator>();

        return obj;
    }
}