#include "AssetSettings.h"
#include "Engine/Resource/ResourceManager.h"

namespace Bisang
{
    void AssetSettings::Apply(ResourceManager* resourceManager)
    {
		Vector3 playerTexPivot = { -12.5,-20,0 };
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/Default/Player1_Front.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/Default/Player1_Back.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/Default/Player1_Left.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/Default/Player1_Right.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/Default/Player1_BackLeft.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/Default/Player1_BackRight.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/Default/Player1_FrontLeft.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/Default/Player1_FrontRight.png")->SetPivot(playerTexPivot);

		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/HandsUp/Player1_RaiseHand_Front.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/HandsUp/Player1_RaiseHand_Back.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/HandsUp/Player1_RaiseHand_Left.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/HandsUp/Player1_RaiseHand_Right.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/HandsUp/Player1_RaiseHand_BackLeft.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/HandsUp/Player1_RaiseHand_BackRight.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/HandsUp/Player1_RaiseHand_FrontLeft.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player1/HandsUp/Player1_RaiseHand_FrontRight.png")->SetPivot(playerTexPivot);

		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/Default/Player2_Front.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/Default/Player2_Back.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/Default/Player2_Left.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/Default/Player2_Right.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/Default/Player2_BackLeft.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/Default/Player2_BackRight.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/Default/Player2_FrontLeft.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/Default/Player2_FrontRight.png")->SetPivot(playerTexPivot);

		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/HandsUp/Player2_RaiseHand_Front.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/HandsUp/Player2_RaiseHand_Back.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/HandsUp/Player2_RaiseHand_Left.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/HandsUp/Player2_RaiseHand_Right.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/HandsUp/Player2_RaiseHand_BackLeft.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/HandsUp/Player2_RaiseHand_BackRight.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/HandsUp/Player2_RaiseHand_FrontLeft.png")->SetPivot(playerTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Player2/HandsUp/Player2_RaiseHand_FrontRight.png")->SetPivot(playerTexPivot);

		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Left.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Right.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Back.png")->SetPivot({ -20, -40, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Front.png")->SetPivot({ -20, -40, 0 });

		//Setting Trees' Pivot
		resourceManager->LoadTexture(L"Assets/Textures/Maps/Terrian/Tree.png")->SetPivot({ 0, -10, 0 });
		resourceManager->LoadTexture(L"Assets/Textures/Maps/Terrian/OrcTree.png")->SetPivot({ 0, -10, 0 });

		Vector3 princessTexPivot = { -17.5,-35,0 };
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Front.png")->SetPivot(princessTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Back.png")->SetPivot(princessTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Left.png")->SetPivot(princessTexPivot);
		resourceManager->LoadTexture(L"Assets/Textures/Characters/Princess/Princess_Right.png")->SetPivot(princessTexPivot);

		resourceManager->LoadTexture(L"Assets/Textures/Characters/Monsters/Rabbit Monster.png")->SetPivot({-800,-800,0});


		//ÀÚ¿ø ÇÇº¿
		resourceManager->LoadTexture(L"Assets/Textures/Maps/Resource/Clay Resource.png")->SetPivot({ 0,5,0 });
		resourceManager->LoadTexture(L"Assets/Textures/Maps/Resource/Tree Resource.png")->SetPivot({ 0,5,0 });


    }
}