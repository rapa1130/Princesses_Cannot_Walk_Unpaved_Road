#pragma once
#include "Engine/Components/Script.h"
#include "Engine/Components/AudioSource/AudioSource.h"
#include "Engine/Resource/AudioClip.h"
#include <unordered_map>
#include <string>
#include <memory>

namespace Bisang
{
    class AudioManager : public Script
    {
    public:
        AudioManager(GameObject* ownerObj) : Script(ownerObj) {}

        void Awake() override;
        void Start() override;

        void Play(const std::string& name, float volume = 1.0f);
        void PlayLoop(const std::string& name, float volume = 1.0f);

        void PlayPickAxeSound();
        void PlayAxeSound();
        void PlayHammerSound();
        void PlayPickUpSound();
        void PlayPutDownSound();
        void PlayOverSound();
        void PlayGiantStepSound(float volume);
        void PlayWoodPutSound();
        void PlayMainBgm();
        void PlayClearBgm();
        void PlayPlayBgm();
        void PlayStoryBgm();

    private:
        void Load(const std::string& name, const std::wstring& path);
        


    private:
        AudioSource* m_audioSource = nullptr;
        std::unordered_map<std::string, std::shared_ptr<AudioClip>> m_clips;
    };
}