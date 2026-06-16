#include "AudioSource.h"

#pragma comment(lib, "xaudio2.lib")

namespace Bisang
{
    IXAudio2* AudioSource::s_xaudio = nullptr;
    IXAudio2MasteringVoice* AudioSource::s_masterVoice = nullptr;

    AudioSource::AudioSource(GameObject* ownerObj)
        : Component(ownerObj)
    {
        InitAudioEngine();
    }

    AudioSource::~AudioSource()
    {
        StopAll();
    }

    bool AudioSource::InitAudioEngine()
    {
        if (s_xaudio != nullptr)
            return true;

        if (FAILED(XAudio2Create(&s_xaudio, 0, XAUDIO2_DEFAULT_PROCESSOR)))
            return false;

        if (FAILED(s_xaudio->CreateMasteringVoice(&s_masterVoice)))
            return false;

        return true;
    }

    void AudioSource::Play(std::shared_ptr<AudioClip> clip, float volume, bool loop)
    {
        if (clip == nullptr || s_xaudio == nullptr)
            return;

        IXAudio2SourceVoice* voice = nullptr;

        if (FAILED(s_xaudio->CreateSourceVoice(&voice, clip->GetFormat())))
            return;

        XAUDIO2_BUFFER buffer = {};
        buffer.AudioBytes = clip->GetDataSize();
        buffer.pAudioData = clip->GetData();
        buffer.Flags = XAUDIO2_END_OF_STREAM;

        if (loop)
            buffer.LoopCount = XAUDIO2_LOOP_INFINITE;

        voice->SetVolume(volume);
        voice->SubmitSourceBuffer(&buffer);
        voice->Start();

        m_voices.push_back({ voice, clip });
    }

    void AudioSource::Update(float dT)
    {
        for (auto it = m_voices.begin(); it != m_voices.end();)
        {
            XAUDIO2_VOICE_STATE state;
            it->voice->GetState(&state);

            if (state.BuffersQueued == 0)
            {
                it->voice->DestroyVoice();
                it = m_voices.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    void AudioSource::StopAll()
    {
        for (PlayingVoice& playing : m_voices)
        {
            if (playing.voice == nullptr) continue;

            playing.voice->Stop();
            playing.voice->FlushSourceBuffers();
            playing.voice->DestroyVoice();
        }

        m_voices.clear();
    }
}