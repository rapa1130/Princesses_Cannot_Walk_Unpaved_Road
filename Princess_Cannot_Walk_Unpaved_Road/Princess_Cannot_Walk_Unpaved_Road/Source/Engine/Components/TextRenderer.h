#pragma once
#include "Engine/Components/Component.h"
#include"Engine/Renderer/Color.h"
#include<string>
#include <memory>

namespace Bisang
{
	class Transform;
	class TextFormatResource;

	class TextRenderer : public RenderableComponent
	{
	public:
		TextRenderer(GameObject* ownerObj);

		void DrawCall(Renderer* renderer) override;


		//Getters
		std::wstring GetText() const;
		Bisang::Color GetColor() const;
		std::wstring GetFontName() const;
		float GetFontSize() const;
		float GetWidth() const;

		//Setters
		void SetTextFormat(std::shared_ptr<TextFormatResource> textFormat);
		void SetText(const std::wstring& text);
		void SetColor(const Bisang::Color& color);
		
	private:

		std::shared_ptr<TextFormatResource> m_textFormat = nullptr;
		std::wstring m_text = L"text";
		Bisang::Color m_color = Bisang::Color::Green;
		float m_width = 200.0f;
	};
}

