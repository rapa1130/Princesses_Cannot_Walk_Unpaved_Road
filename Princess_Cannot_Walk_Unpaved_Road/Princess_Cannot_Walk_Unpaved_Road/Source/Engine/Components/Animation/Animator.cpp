#include "Animator.h"
#include "Engine/Object/GameObject.h"
#include "Engine/Components/SpriteRenderer.h"
#include "Engine/Core/Debug.h"

namespace Bisang
{
    Animator::Animator(GameObject* ownerObj)
        : Component(ownerObj)
    {
    }

    void Animator::Start()
    {
        m_spriteRenderer = m_ownerObj->GetComponent<SpriteRenderer>();
        if (m_spriteRenderer == nullptr)
        {
            DEBUG_ERROR("Animator컴포넌트에는 SpriteRenderer Component가 필요합니다");
        }
    }

    void Animator::Update(float dT)
    {
        if (!m_isPlaying)
            return;

        if (m_spriteRenderer == nullptr)
            return;

        auto iter = m_clips.find(m_currentClipName);

        if (iter == m_clips.end())
            return;

        AnimationClip& clip = iter->second;

        if (clip.frames.empty())
            return;

        AnimationFrame& currentFrame = clip.frames[m_currentFrameIndex];

        m_elapsedTime += dT;

        if (m_elapsedTime < currentFrame.duration)
            return;

        m_elapsedTime = 0.0f;
        m_currentFrameIndex++;

        if (m_currentFrameIndex >= static_cast<int>(clip.frames.size()))
        {
            if (clip.loop)
            {
                m_currentFrameIndex = 0;
            }
            else
            {
                m_currentFrameIndex = static_cast<int>(clip.frames.size()) - 1;
                m_isPlaying = false;
            }
        }

        AnimationFrame& nextFrame = clip.frames[m_currentFrameIndex];
        m_spriteRenderer->SetSprite(nextFrame.sprite);
    }

    void Animator::AddClip(const AnimationClip& clip)
    {
        m_clips[clip.name] = clip;
    }

    void Animator::SetClip(const std::wstring& clipName)
    {
        if (m_currentClipName == clipName && m_isPlaying)
            return;

        auto iter = m_clips.find(clipName);

        if (iter == m_clips.end())
            return;

        m_currentClipName = clipName;
        m_currentFrameIndex = 0;
        m_elapsedTime = 0.0f;
        m_isPlaying = true;

        AnimationClip& clip = iter->second;

        if (!clip.frames.empty() && m_spriteRenderer != nullptr)
        {
            m_spriteRenderer->SetSprite(clip.frames[0].sprite);
        }
    }

    void Animator::Stop()
    {
        m_isPlaying = false;
    }

    void Animator::Play()
    {
        m_isPlaying = true;
    }

    void Animator::SetLoop(const std::wstring& clipName, bool loop)
    {
        auto iter = m_clips.find(clipName);

        if (iter == m_clips.end())
            return;

        iter->second.loop = loop;
    }
}