#include "AudioManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Resource/ResourceManager.h"

#include <iostream>

namespace Bisang
{
    void AudioManager::Start()
    {
        m_audioSource = m_ownerObj->GetComponent<AudioSource>();

        Load("BGM", L"Assets/Sounds/Bgm.wav");
        Load("PickAxe", L"Assets/Sounds/PickAxe.wav");
        Load("Axe", L"Assets/Sounds/Axe.wav");
        Load("Hammer", L"Assets/Sounds/Hammer.wav");
        Load("PickUp", L"Assets/Sounds/PickUp.wav");
        Load("PutDown", L"Assets/Sounds/PutDown.wav");
        Load("GiantStep", L"Assets/Sounds/GiantStep.wav");
        Load("WoodPut", L"Assets/Sounds/WoodPut.wav");

        PlayBgm();
    }

    void AudioManager::Load(const std::string& name, const std::wstring& path)
    {
        m_clips[name] = GetResourceManager()->LoadAudioClip(path);
    }

    void AudioManager::Play(const std::string& name, float volume)
    {
        auto it = m_clips.find(name);
        if (it == m_clips.end()) return;

        m_audioSource->Play(it->second, volume, false);
    }

    void AudioManager::PlayLoop(const std::string& name, float volume)
    {
        auto it = m_clips.find(name);
        if (it == m_clips.end()) return;

        m_audioSource->Play(it->second, volume, true);
    }

    void AudioManager::PlayBgm()
    {
        PlayLoop("BGM", 0.3);
    }

    void AudioManager::PlayPickAxeSound()
    {
        Play("PickAxe", 1);
    }

    void AudioManager::PlayAxeSound()
    {
        Play("Axe", 1);
    }

    void AudioManager::PlayHammerSound()
    {
        Play("Hammer", 1);
    }

    void AudioManager::PlayPickUpSound()
    {
        Play("PickUp", 0.5);
    }

    void AudioManager::PlayPutDownSound()
    {
        Play("PutDown", 1);
    }

    void AudioManager::PlayGiantStepSound(float volume)
    {
        Play("GiantStep", volume);
    }

    void AudioManager::PlayWoodPutSound()
    {
        Play("WoodPut", 1);
    }
}