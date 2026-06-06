#pragma once
#include "Engine/Components/Component.h"
#include<memory>
#include<string>

namespace Bisang
{
	class Transform;
	class TextureResource;

	class SpriteRenderer : public RenderableComponent
	{
	public:
		SpriteRenderer(GameObject* ownerObj, Scene* scene);

		void DrawCall(Renderer* renderer) override;

		void SetSprite(std::shared_ptr<TextureResource> sprite);
		void SetSprite(const std::wstring& path);

		float GetAlpha() const { return m_alpha; }
		float GetWidth() const;
		float GetHeight() const;

		void SetAlpha(float alpha) { m_alpha = alpha; }
		void SetWidth(int width) { m_width = width; }
		void SetHeight(int height) { m_height = height; }
	private:
		std::shared_ptr<TextureResource> m_sprite = nullptr;

		float m_alpha = 1.0f;   // 알파
		float m_width = 0;        // 너비
		float m_height = 0;       // 높이
	};
}