#pragma once

#include"DxHeaders.h"
#include<vector>
#include"IRenderable.h"
#include"Engine/Resource/ResourceManager.h"
#include <typeindex>
#include <type_traits>
#include"Engine/Math/Vector2.h"

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

	struct RenderCommand
	{

		//std::type_index type;

		RenderCommandType type = RenderCommandType::None;
		IResource* resource = nullptr;
		int orderInLayer = orderInLayer;
		Vector2 position;

		template<typename T>
		T* GetResourceAs() const
		{
			return dynamic_cast<T*>(resource);
		}
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

		std::shared_ptr<TextureResource> LoadTexture(
			const std::wstring& path
		);

		ID2D1DeviceContext4* GetD2DContext() const
		{
			return m_d2dContext.Get();
		}

	protected:

	protected:
		D2D1::ColorF m_BgColor = D2D1::ColorF::White;
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