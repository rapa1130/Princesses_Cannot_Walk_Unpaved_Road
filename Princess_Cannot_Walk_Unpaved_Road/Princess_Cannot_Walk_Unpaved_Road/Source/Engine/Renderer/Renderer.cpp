#include "Renderer.h"
#include<algorithm>
#include"Engine/Components/Component.h"
#include"Engine/Core/GameApp.h"
#include"Engine/Scene/SceneManager.h"
#include"Engine/Scene/Scene.h"


namespace Bisang
{

    bool Renderer::Initialize( HWND hwnd, int width, int height)
    {
        //1. D3D11 디바이스 생성
        D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };
        ComPtr<ID3D11Device> d3dDevice;
        ComPtr<ID3D11DeviceContext> d3dContext;

        HRESULT hr = D3D11CreateDevice(
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            nullptr,
            D3D11_CREATE_DEVICE_BGRA_SUPPORT,
            featureLevels,
            ARRAYSIZE(featureLevels),
            D3D11_SDK_VERSION,
            &d3dDevice,
            nullptr,
            &d3dContext);

        if (FAILED(hr)) return false;



        //DXGI 디바이스 (어댑터/공유리소스 관리용)
        ComPtr<IDXGIDevice> dxgiDevice;
        hr = d3dDevice.As(&dxgiDevice);
        if (FAILED(hr)) return false;



        //실제 GPU 어댑터 (NVIDIA, AMD 등)
        ComPtr<IDXGIAdapter> dxgiAdapter;
        hr = dxgiDevice->GetAdapter(&dxgiAdapter);
        if (FAILED(hr)) return false;


        //DXGI 팩토리 (스왑체인 생성을 하기 위해 필요)
        ComPtr<IDXGIFactory2> dxgiFactory;
        hr = dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
        if (FAILED(hr)) return false;


        DXGI_SWAP_CHAIN_DESC1 scDesc = {};
        scDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        scDesc.SampleDesc.Count = 1; //Flip-모델은 다중 샘플 백버퍼를 직접 지원하지X -> 반드시 1
        scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        scDesc.BufferCount = 2; // 더블 버퍼(Back + Front)
        scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
        scDesc.Scaling = DXGI_SCALING_STRETCH;



        ComPtr<IDXGISwapChain1> swapChain;
        hr = dxgiFactory->CreateSwapChainForHwnd(
            d3dDevice.Get(), hwnd, &scDesc, nullptr, nullptr, &swapChain);
        if (FAILED(hr)) return false;


        // 3. ID2D1Factory4 생성
        D2D1_FACTORY_OPTIONS opts = {};
        ComPtr<ID2D1Factory4> d2dFactory;

        hr = D2D1CreateFactory(
            D2D1_FACTORY_TYPE_SINGLE_THREADED,
            __uuidof(ID2D1Factory4),
            &opts,
            reinterpret_cast<void**>(d2dFactory.GetAddressOf()));
        if (FAILED(hr)) return false;


        // 4. ID2D1Device4 생성
        ComPtr<ID2D1Device> baseDevice;
        hr = d2dFactory->CreateDevice(dxgiDevice.Get(), &baseDevice);
        if (FAILED(hr)) return false;

        ComPtr<ID2D1Device4> d2dDevice;
        hr = baseDevice.As(&d2dDevice);
        if (FAILED(hr)) return false;


        // 5. ID2D1DeviceContext4 생성
        ComPtr<ID2D1DeviceContext4> d2dContext;
        hr = d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &d2dContext);
        if (FAILED(hr)) return false;


        // 6. SwapChain 백버퍼 -> D2D Bitmap1 을 생성하여 렌더 타겟으로 설정

        ComPtr<IDXGISurface> dxgiSurface;
        hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&dxgiSurface));
        if (FAILED(hr)) return false;

        D2D1_BITMAP_PROPERTIES1 bitmapProps = {};
        bitmapProps.bitmapOptions = D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW;
        bitmapProps.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
        bitmapProps.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
        bitmapProps.dpiX = bitmapProps.dpiY = 96.0f;

        ComPtr<ID2D1Bitmap1> targetBitmap;
        hr = d2dContext->CreateBitmapFromDxgiSurface(dxgiSurface.Get(), &bitmapProps, targetBitmap.GetAddressOf());
        if (FAILED(hr)) return false;

        // 렌더 타겟 설정
        d2dContext->SetTarget(targetBitmap.Get());



        // 7. 기본 브러시 생성
        ComPtr<ID2D1SolidColorBrush> brush;
        hr = d2dContext->CreateSolidColorBrush(
            D2D1::ColorF(D2D1::ColorF::Tomato), &brush);
        if (FAILED(hr)) return false;

        // 8. 멤버로 저장
        m_d3dDevice = d3dDevice;
        m_d3dContext = d3dContext;
        m_swapChain = swapChain;
        m_d2dFactory = d2dFactory;
        m_d2dDevice = d2dDevice;
        m_d2dContext = d2dContext;
        m_targetBitmap = targetBitmap;
        m_brush = brush;

        return true;

    }





    void Renderer::RenderScene(Scene* scene)
    {
        if (!m_d2dContext || !m_swapChain)
            return;

        m_d2dContext->BeginDraw();

        m_d2dContext->Clear(m_BgColor);
        scene->Render(this);
        m_d2dContext->EndDraw();

        m_swapChain->Present(1, 0);
    }

    void Renderer::Sumbit()
    {
    }




    
    
}



