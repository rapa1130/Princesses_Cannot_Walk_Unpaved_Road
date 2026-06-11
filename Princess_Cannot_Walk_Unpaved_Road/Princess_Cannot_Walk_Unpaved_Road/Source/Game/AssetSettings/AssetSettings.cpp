#include "AssetSettings.h"
#include "Engine/Resource/ResourceManager.h"

namespace Bisang
{
    void AssetSettings::Apply(ResourceManager* resourceManager)
    {
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Front.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Back.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Left.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_Right.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_BackLeft.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_BackRight.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_FrontLeft.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player/Player_FrontRight.png")->SetPivot({ -20, -40, 0 });

		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Left.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Right.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Back.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Front.png")->SetPivot({ -20, -40, 0 });
    }
}