#pragma once

#include"DxHeaders.h"
#include<vector>
#include"IRenderable.h"
#include"Engine/Resource/ResourceManager.h"
#include <typeindex>
#include <type_traits>

//
// @brief D2D 렌더링 Wrapper 클래스
//
// D2D 기능들을 Wrapping 하여
// 외부에 렌더링 기능을 제공



namespace Bisang
{
	class Scene;
	class ResourceManager;

	template<typename T>
	struct RenderCommand
	{
		std::type_index type;
		IResource resource;
		int orderInLayer;
	};

	class Renderer
	{
	public:
		bool Initialize(HWND hwnd, int width, int height);
		void RenderScene(Scene* scene);
		void Sumbit();

	protected:

	protected:
		D2D1::ColorF m_BgColor = D2D1::ColorF::White;
		std::vector<IRenderable*> m_Rendarables;

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