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
		Vector3 position;
		Vector2 size;
		float rot;
		float alpha;
	};

	struct LineCommandData
	{
		Vector3 start;
		Vector3 end;
		float thickness;
		Bisang::Color color;
	};

	struct TextCommandData
	{
		const wchar_t* text;
		UINT32 length;

		TextFormatResource* textFormat;

		Vector3 position;
		Vector2 textBoxSize;

		Bisang::Color color;
	};


	struct RenderCommand
	{
		RenderCommandType type;
		int layer;
		float depth;

		union
		{
			SpriteCommandData sprite;
			LineCommandData line;
			TextCommandData text;
		};

		static RenderCommand CreateSpriteRC(
			IResource* resource,
			const Vector3& position,
			const Vector2& size,
			float rot,
			int layer,
			float depth = 1.0f,
			float alpha = 1.0f
		);

		static RenderCommand CreateLineRC(
			const Vector3& start,
			const Vector3& end,
			Bisang::Color color,
			int layer,
			float thickness = 1.0f,
			float depth = 0.0f
		);

		static RenderCommand CreateTextRC(
			const wchar_t* text,
			UINT32 length,
			TextFormatResource* textFormat,
			const Vector3& position,
			const Vector2& size,
			const Bisang::Color& color,
			int layer,
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