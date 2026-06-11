#include "Game/Prefabs/BlockMapPrefab.h"

#include "Engine/Components/Transform.h"
#include "Engine/Components/BlockMap/BlockMap.h"
#include "Engine/Components/BlockMap/BlockMapRenderer.h"
#include "Engine/Resource/ResourceManager.h"
#include "Engine/Core/Layer.h"
#include <random>
#include "Game/Scripts/PlayerController.h"

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
        bMap->InitMap(30, 30, 90);

		for (int i = 0; i < 10; i++)
		{
			for (int ii = 0; ii < 10; ii++)
			{
				for (int iii = 0; iii <= 0; iii++)
				{
					bMap->SetBlock({ i, ii, iii }, BlockId::Grass);
				}
			}
		}
		srand(time(NULL));



		BlockMapRenderer* bMapR = obj->AddComponent<BlockMapRenderer>();
		bMapR->SetLayer(Layer::Iso);
		bMapR->SetBlockMap(bMap);


		std::unordered_map<int, std::shared_ptr<TextureResource>> textures =
		{
			{static_cast<int>(BlockId::Grass), m_resourceManager->LoadTexture(L"Assets/Textures/GrassBlock.png")},
			{static_cast<int>(BlockId::Dirt), m_resourceManager->LoadTexture(L"Assets/Textures/Dirt.png")},
			{static_cast<int>(BlockId::Water), m_resourceManager->LoadTexture(L"Assets/Textures/Water.png")},
			{static_cast<int>(BlockId::Rock), m_resourceManager->LoadTexture(L"Assets/Textures/Rock.png")},
			{static_cast<int>(BlockId::Clay), m_resourceManager->LoadTexture(L"Assets/Textures/Clay.png")},
			{static_cast<int>(BlockId::Tree), m_resourceManager->LoadTexture(L"Assets/Textures/Tree.png")},
			{static_cast<int>(BlockId::OrcTree), m_resourceManager->LoadTexture(L"Assets/Textures/OrcTree.png")}
		};
		
		bMapR->SetBlockTextures(textures);


        return obj;
    }
}