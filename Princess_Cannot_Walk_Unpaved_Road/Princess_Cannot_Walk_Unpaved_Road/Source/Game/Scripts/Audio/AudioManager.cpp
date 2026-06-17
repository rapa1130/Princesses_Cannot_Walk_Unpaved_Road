#include "AudioManager.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Resource/ResourceManager.h"

#include <iostream>

namespace Bisang
{
    void AudioManager::Awake()
    {
        m_audioSource = m_ownerObj->GetComponent<AudioSource>();

        Load("PickAxe", L"Assets/Sounds/PickAxe.wav");
        Load("Axe", L"Assets/Sounds/Axe.wav");
        Load("Hammer", L"Assets/Sounds/Hammer.wav");
        Load("PickUp", L"Assets/Sounds/PickUp.wav");
        Load("PutDown", L"Assets/Sounds/PutDown.wav");
        Load("GiantStep", L"Assets/Sounds/GiantStep.wav");
        Load("WoodPut", L"Assets/Sounds/WoodPut.wav");
        Load("Main", L"Assets/Sounds/Main.wav");
        Load("Clear", L"Assets/Sounds/Clear.wav");
        Load("Over", L"Assets/Sounds/Over.wav");
        Load("Play", L"Assets/Sounds/Play.wav");
        Load("Story", L"Assets/Sounds/Story.wav");
    }

    void AudioManager::Start()
    {

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

    void AudioManager::PlayMainBgm()
    {
        PlayLoop("Main", 1);
    }

    void AudioManager::PlayClearBgm()
    {
        PlayLoop("Clear", 1);
    }

    void AudioManager::PlayOverSound()
    {
        Play("Over", 1);
    }

    void AudioManager::PlayPickAxeSound()
    {
        Play("PickAxe", 1.2);
    }

    void AudioManager::PlayAxeSound()
    {
        Play("Axe", 1.2);
    }

    void AudioManager::PlayHammerSound()
    {
        Play("Hammer", 1.2);
    }

    void AudioManager::PlayPickUpSound()
    {
        Play("PickUp", 0.8);
    }

    void AudioManager::PlayPutDownSound()
    {
        Play("PutDown", 0.8);
    }

    void AudioManager::PlayGiantStepSound(float volume)
    {
        Play("GiantStep", volume + 0.4);
    }

    void AudioManager::PlayWoodPutSound()
    {
        Play("WoodPut", 1.8);
    }

    void AudioManager::PlayPlayBgm()
    {
        PlayLoop("Play", 0.5);
    }

    void AudioManager::PlayStoryBgm()
    {
        PlayLoop("Story", 1);
    }
}