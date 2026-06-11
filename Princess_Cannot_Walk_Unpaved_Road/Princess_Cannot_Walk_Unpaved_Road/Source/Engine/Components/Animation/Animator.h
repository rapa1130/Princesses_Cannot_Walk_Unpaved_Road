#pragma once
#include "Engine/Components/Component.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>


namespace Bisang
{
    class Transform;
    class TextureResource;
    class SpriteRenderer;

    struct AnimationFrame
    {
        std::shared_ptr<TextureResource> sprite = nullptr;
        float duration = 0.1f; // 이 프레임을 유지할 시간
    };

    struct AnimationClip
    {
        std::wstring name;
        std::vector<AnimationFrame> frames;
        bool loop = true;
    };

    class Animator : public Component
    {
    public:
        Animator(GameObject* ownerObj);

        void Start() override;
        void Update(float dT) override;

        void AddClip(const AnimationClip& clip);
        void SetClip(const std::wstring& clipName);
        void Stop();
        void Play();


        void SetLoop(const std::wstring& clipName, bool loop);

        const std::wstring& GetCurrentClipName() const { return m_currentClipName; }

    private:
        SpriteRenderer* m_spriteRenderer = nullptr;

        std::unordered_map<std::wstring, AnimationClip> m_clips;

        std::wstring m_currentClipName;
        int m_currentFrameIndex = 0;
        float m_elapsedTime = 0.0f;

        bool m_isPlaying = false;
    };
}