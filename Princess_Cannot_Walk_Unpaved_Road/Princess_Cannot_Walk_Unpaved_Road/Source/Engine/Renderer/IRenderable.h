#pragma once

namespace Bisang
{
	class Renderer;

	class IRenderable
	{
	public:
		virtual void DrawCall(Renderer* renderer) = 0;
		virtual ~IRenderable() = default;
	};
}