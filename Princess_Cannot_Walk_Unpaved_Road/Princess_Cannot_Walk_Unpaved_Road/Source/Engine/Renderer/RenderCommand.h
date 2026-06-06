#pragma once

#include"Engine/Renderer/Color.h"


namespace Bisang
{
	enum class RenderCommandType
	{
		None,
		Sprite,
		Text,
		Line,
		Rectangle
	};


	struct SpriteCommandData
	{
		IResource* resource;
		Vector2 position;
		Vector2 size;
		float rot;
		float alpha;
	};

	struct LineCommandData
	{
		Vector2 start;
		Vector2 end;
		float thickness;
		Bisang::Color color;
	};

	struct TextCommandData
	{
		const wchar_t* text;
		UINT32 length;

		TextFormatResource* textFormat;

		Vector2 position;
		Vector2 textBoxSize;

		Bisang::Color color;
	};


	struct RenderCommand
	{
		RenderCommandType type;
		int orderInLayer;
		float depth;

		union
		{
			SpriteCommandData sprite;
			LineCommandData line;
			TextCommandData text;
		};

		static RenderCommand CreateSpriteRC(
			IResource* resource,
			const Vector2& position,
			const Vector2& size,
			float rot,
			int orderInLayer,
			float depth = 1.0f,
			float alpha = 1.0f
		);

		static RenderCommand CreateLineRC(
			const Vector2& start,
			const Vector2& end,
			Bisang::Color color,
			int orderInLayer,
			float thickness = 1.0f,
			float depth = 0.0f
		);

		static RenderCommand CreateTextRC(
			const wchar_t* text,
			UINT32 length,
			TextFormatResource* textFormat,
			const Vector2& position,
			const Vector2& size,
			const Bisang::Color& color,
			int orderInLayer,
			float depth = 0.0f
		);

		template<typename T>
		T* GetResourceAs(IResource* resource) const
		{
			return dynamic_cast<T*>(resource);
		}

	private:
		RenderCommand() {}
	};
}