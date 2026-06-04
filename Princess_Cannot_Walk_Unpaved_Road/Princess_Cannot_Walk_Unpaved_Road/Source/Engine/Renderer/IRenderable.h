#pragma once

namespace Bisang
{
	class Renderer;

	class IRenderable
	{
	public:
		virtual void Render(Renderer& renderer) = 0;
		//virtual ~IRenderable() = default;
	};
}