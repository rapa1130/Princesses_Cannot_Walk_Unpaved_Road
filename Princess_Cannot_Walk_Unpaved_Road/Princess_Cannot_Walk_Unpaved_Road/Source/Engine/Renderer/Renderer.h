#pragma once

#include"DxHeaders.h"
#include<vector>
#include"IRenderable.h"
#include"Engine/Resource/ResourceManager.h"
#include <typeindex>
#include <type_traits>
#include"Engine/Math/Vector2.h"
#include"Engine/Renderer/Color.h"

//
// @brief D2D 렌더링 Wrapper 클래스
//
// D2D 기능들을 Wrapping 하여
// 외부에 렌더링 기능을 제공



namespace Bisang
{
	class Scene;
	class ResourceManager;

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


	struct RenderCommand
	{
		RenderCommandType type;
		int orderInLayer;
		float depth;
		
		union
		{
			SpriteCommandData sprite;
			LineCommandData line;
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

		template<typename T>
		T* GetResourceAs(IResource* resource) const
		{
			return dynamic_cast<T*>(resource);
		}

	private:
		RenderCommand() {}
	};

	class Renderer
	{
	public:
		Renderer(ResourceManager* resourceManager)
			:m_resourceManager(resourceManager) { }

		bool Initialize(HWND hwnd, int width, int height);
		void RenderScene(Scene* scene);
		void RenderAllCommands();
		void Submit(const RenderCommand& command);
		void RenderSprite(const RenderCommand& command);
		void RenderLine(const RenderCommand& command);

		//std::shared_ptr<TextureResource> LoadTexture(
		//	const std::wstring& path
		//);

		ID2D1DeviceContext4* GetD2DContext() const
		{
			return m_d2dContext.Get();
		}

	protected:

	protected:
		D2D1::ColorF m_BgColor = D2D1::ColorF::Black;
		std::vector<RenderCommand> m_renderCommands;
	protected:
		ResourceManager* m_resourceManager;

	protected:
		// D3D11
		ComPtr<ID3D11Device>           m_d3dDevice;
		ComPtr<ID3D11DeviceContext>    m_d3dContext;

		// DXGI
		ComPtr<IDXGISwapChain1>        m_swapChain;

		// Direct2D 최신 인터페이스
		ComPtr<ID2D1Factory4>          m_d2dFactory;
		ComPtr<ID2D1Device4>           m_d2dDevice;
		ComPtr<ID2D1DeviceContext4>    m_d2dContext;

		// Direct2D 이전 인터페이스
		ComPtr<ID2D1HwndRenderTarget> m_renderTarget;

		// Background
		ComPtr<ID2D1SolidColorBrush> m_brush;

		// Offscreen RenderTarget
		ComPtr<ID2D1Bitmap1>          m_targetBitmap;
	};
}