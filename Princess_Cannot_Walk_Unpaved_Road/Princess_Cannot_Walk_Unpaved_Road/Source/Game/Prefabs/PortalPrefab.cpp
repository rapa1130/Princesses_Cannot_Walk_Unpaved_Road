#include "PortalPrefab.h"
#include "Engine/Components/Transform.h"
#include "Engine/Object/GameObject.h"
#include "Game/Scripts/Portal/PortalParticle.h"
#include "Engine/Components/SpriteRenderer.h"

namespace Bisang
{
	std::unique_ptr<GameObject> PortalParticlePrefab::Instantiate()
	{
		std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
		obj->SetName("PortalParticle");

		auto* tf = obj->GetComponent<Transform>();
		auto* sr = obj->AddComponent<SpriteRenderer>();
		auto* portal = obj->AddComponent<PortalParticle>();

		return obj;
	}
}