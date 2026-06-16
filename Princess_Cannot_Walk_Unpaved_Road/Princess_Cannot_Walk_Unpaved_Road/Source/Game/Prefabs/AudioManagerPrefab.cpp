#include "AudioManagerPrefab.h"

#include "Game/Scripts/Audio/AudioManager.h"
#include "Engine/Resource/AudioClip.h"

namespace Bisang
{
	std::unique_ptr<GameObject> AudioManagerPrefab::Instantiate()
	{
        auto obj = std::make_unique<GameObject>();
        obj->SetName("AudioManager");

        obj->AddComponent<AudioSource>();
        obj->AddComponent<AudioManager>();

        return obj;
	}
}