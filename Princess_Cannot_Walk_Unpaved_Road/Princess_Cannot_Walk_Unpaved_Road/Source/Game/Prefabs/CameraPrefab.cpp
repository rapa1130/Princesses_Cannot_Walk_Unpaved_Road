#include "CameraPrefab.h"
#include "Engine/Components/Camera/Camara2D.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Camera/CameraController.h"

namespace Bisang
{
	std::unique_ptr<GameObject> CameraPrefab::Instantiate()
	{
		std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
		obj->SetName("Camera");

		obj->AddComponent<Camera2D>();
		obj->AddComponent<CameraController>();

		return obj;
	}
}