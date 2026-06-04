#pragma once


#include <wincodec.h>
#include <iostream>
#include "D2DBitmapInfo.h"

#pragma comment(lib, "windowscodecs.lib")  // WIC 라이브러리
#pragma comment(lib, "msimg32.lib")        // AlphaBlend 함수가 포함된 라이브러리

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;


namespace Bisang
{
    struct WICInitializer
    {
        WICInitializer() = default;

        ~WICInitializer()
        {
            CoUninitialize();
        }




        bool Initialize()
        {
            HRESULT lastError = S_OK;

            lastError = CoCreateInstance(
                CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pFactory));

            if (FAILED(lastError))
            {
                m_pFactory = nullptr;
                return false;
            }

            return true;
        }



        bool LoadImageFromFile(
            LPCWSTR filename,
            ID2D1DeviceContext* d2dContext,
            ComPtr<ID2D1Bitmap1>& outBitmap
        )
        {
            outBitmap.Reset();





            if (m_pFactory == nullptr || d2dContext == nullptr)
            {
                lastError = E_FAIL;
                return false;
            }



            lastError = m_pFactory->CreateDecoderFromFilename(
                filename,
                nullptr,
                GENERIC_READ,
                WICDecodeMetadataCacheOnLoad,
                &m_pDecoder
            );

            if (FAILED(lastError))
                return false;

            lastError = m_pDecoder->GetFrame(0, &m_pFrame);

            if (FAILED(lastError))
                return false;

            lastError = m_pFactory->CreateFormatConverter(&m_pConverter);

            if (FAILED(lastError))
                return false;

            lastError = m_pConverter->Initialize(
                m_pFrame.Get(),
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.0f,
                WICBitmapPaletteTypeCustom
            );

            if (FAILED(lastError))
                return false;

            D2D1_BITMAP_PROPERTIES1 bitmapProps =
                D2D1::BitmapProperties1(
                    D2D1_BITMAP_OPTIONS_NONE,
                    D2D1::PixelFormat(
                        DXGI_FORMAT_B8G8R8A8_UNORM,
                        D2D1_ALPHA_MODE_PREMULTIPLIED
                    )
                );

            lastError = d2dContext->CreateBitmapFromWicBitmap(
                m_pConverter.Get(),
                bitmapProps,
                &outBitmap
            );

            if (FAILED(lastError))
                return false;

            return true;
        }

        ComPtr<IWICImagingFactory> m_pFactory = nullptr;
        ComPtr<IWICBitmapDecoder> m_pDecoder = nullptr;
        ComPtr<IWICBitmapFrameDecode> m_pFrame = nullptr;
        ComPtr<IWICFormatConverter> m_pConverter = nullptr;

        HRESULT lastError = S_OK;



        void Clean()
        {
            if (m_pDecoder) m_pDecoder->Release();
            if (m_pFrame) m_pFrame->Release();
            if (m_pConverter) m_pConverter->Release();
        }

        DxBitmapInfo* CreateBitmapInfo(ComPtr<ID2D1Bitmap1> hBitmap)
        {
            DxBitmapInfo* pNewBitmap = new DxBitmapInfo(hBitmap);

            return pNewBitmap;
        }

    }GWICInitializer;


    DxBitmapInfo* CreateBitmapInfo(ID2D1DeviceContext* d2dDC, LPCWSTR filename)
    {
        static bool bCoInit = GWICInitializer.Initialize();
        if (false == bCoInit)
        {
            return nullptr;
        }

        ComPtr<ID2D1Bitmap1> bitmap = nullptr;
        DxBitmapInfo* pBitmapInfo = nullptr;
        if (GWICInitializer.LoadImageFromFile(filename, d2dDC, bitmap))
        {
            pBitmapInfo = GWICInitializer.CreateBitmapInfo(bitmap);
        }

        GWICInitializer.Clean();

        return pBitmapInfo;
    }
}
