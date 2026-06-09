#pragma once

#include"Engine/Renderer/Color.h"
#include"Engine/Math/Vector.h"


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
		Vector3 sortKey;

		union
		{
			SpriteCommandData sprite;
			LineCommandData line;
			TextCommandData text;
		};

		static RenderCommand CreateSpriteRC(
			int layer,
			Vector3 sortKey,
			IResource* resource,
			const Vector3& position,
			const Vector2& size,
			float rot,
			float alpha = 1.0f
		);

		static RenderCommand CreateLineRC(
			int layer,
			Vector3 sortKey,
			const Vector3& start,
			const Vector3& end,
			float thickness = 1.0f,
			Bisang::Color color = Bisang::Color::White
		);

		static RenderCommand CreateTextRC(
			int layer,
			Vector3 sortKey,
			const wchar_t* text,
			UINT32 length,
			TextFormatResource* textFormat,
			const Vector3& position,
			const Vector2& textBoxSize,
			const Bisang::Color& color
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