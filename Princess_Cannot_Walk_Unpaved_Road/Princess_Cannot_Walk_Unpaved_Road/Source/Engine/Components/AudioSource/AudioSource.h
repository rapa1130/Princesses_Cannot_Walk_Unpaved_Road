#pragma once
#include "Engine/Components/Component.h"
#include "Engine/Resource/AudioClip.h"
#include <xaudio2.h>
#include <memory>
#include <vector>

namespace Bisang
{
    class AudioSource : public Component
    {
    public:
        AudioSource(GameObject* ownerObj);
        ~AudioSource();

        void Update(float dT) override;

        void Play(std::shared_ptr<AudioClip> clip, float volume = 1.0f, bool loop = false);
        void StopAll();

    private:
        struct PlayingVoice
        {
            IXAudio2SourceVoice* voice = nullptr;
            std::shared_ptr<AudioClip> clip;
        };

        static bool InitAudioEngine();
        static IXAudio2* s_xaudio;
        static IXAudio2MasteringVoice* s_masterVoice;

        std::vector<PlayingVoice> m_voices;
    };
}