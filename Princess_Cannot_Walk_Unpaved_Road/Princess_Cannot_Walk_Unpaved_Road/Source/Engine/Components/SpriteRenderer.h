#pragma once
#include "Engine/Components/Component.h"
#include <memory>
#include <string>
#include "Engine/Renderer/Color.h"
#include "Engine/Renderer/RenderCommand.h"

namespace Bisang
{
	class Transform;
	class TextureResource;

	class SpriteRenderer : public RenderableComponent
	{
	public:
		SpriteRenderer(GameObject* ownerObj);

		void DrawCall(Renderer* renderer) override;

		void SetSprite(std::shared_ptr<TextureResource> sprite);
		void SetSprite(const std::wstring& path);

		float GetWidth() const;
		float GetHeight() const;
		int GetOrderInZ() const;
		Bisang::Color GetColor() const;
		SpriteDrawFlags GetDrawFlags() const;

		void SetWidth(int width) { m_width = width; }
		void SetHeight(int height) { m_height = height; }
		void SetColor(const Bisang::Color& color) { m_color = color; }
		void SetDrawFlags(SpriteDrawFlags flags) { m_drawFlags = flags; }
		void SetOrderInZ(int orderInZ) { m_orderInZ = orderInZ; }

	private:
		std::shared_ptr<TextureResource> m_sprite = nullptr;

		float m_width = 0;        // 너비
		float m_height = 0;       // 높이

		int m_orderInZ = 0;
		

		Bisang::Color m_color = Bisang::Color::Yellow;
		SpriteDrawFlags m_drawFlags = SpriteDrawFlags::Sprite;
		
	};
}