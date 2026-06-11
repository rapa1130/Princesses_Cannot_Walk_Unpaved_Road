#pragma once

#include"DxHeaders.h"
#include<vector>
#include"IRenderable.h"
#include <typeindex>
#include <type_traits>
#include"Engine/Math/Vector.h"
#include"Engine/Renderer/Color.h"
#include "Engine/Renderer/RenderCommand.h"

//
// @brief D2D 렌더링 Wrapper 클래스
//
// D2D 기능들을 Wrapping 하여
// 외부에 렌더링 기능을 제공

#include<string>

namespace Bisang
{
	class Scene;
	
	class Renderer
	{
	public:

		bool Initialize(HWND hwnd, int width, int height);

		void RenderScene(Scene* scene);
		void RenderAllCommands();

		void Submit(const RenderCommand& command);

		void RenderSprite(const RenderCommand& command);
		void RenderLine(const RenderCommand& command);
		void RenderText(const RenderCommand& command);


		ID2D1DeviceContext4* GetD2DContext() const
		{
			return m_d2dContext.Get();
		}

	protected:

	protected:
		D2D1::ColorF m_BgColor = D2D1::ColorF::Black;
		std::vector<RenderCommand> m_renderCommands;

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


	D2D1_POINT_2F ToD2DPoint(const Bisang::Vector3& v);

}