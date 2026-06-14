#include "DebugOverlay.h"

#include "Engine/Core/Layer.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/Transform.h"
#include "Engine/Components/TextRenderer.h"
#include "Engine/Resource/ResourceManager.h"

#include "Game/Scripts/Debug/Overlay.h"

namespace Bisang
{
	std::unique_ptr<GameObject> DebugOverlay::Instantiate()
	{
		std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
		obj->SetName("DebugOverlay");

		Transform* transform = obj->GetComponent<Transform>();
		transform->SetPosition({1700, 20 , 0});
		transform->SetScale({ 1000, 1 });

		TextRenderer* textRenderer = obj->AddComponent<TextRenderer>();
		textRenderer->SetTextFormat(m_resourceManager->LoadTextFormat(L"¸¼Àº °íµñ", 50));
		textRenderer->SetLayer(Layer::UI);
		textRenderer->SetWidth(1000);

		obj->AddComponent<Overlay>();

		return obj;
	}
}