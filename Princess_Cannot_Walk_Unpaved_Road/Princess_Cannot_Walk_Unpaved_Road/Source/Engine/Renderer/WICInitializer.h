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
            m_LastError = CoCreateInstance(
                CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&m_pFactory));

            if (FAILED(m_LastError))
            {
                m_pFactory = nullptr;
                return false;
            }

            return true;
        }

        bool LoadD2DBitmapFromFile(
            LPCWSTR filename,
            ID2D1DeviceContext* d2dContext,
            ComPtr<ID2D1Bitmap1>& outBitmap
        )
        {
            outBitmap.Reset();

            if (m_pFactory == nullptr || d2dContext == nullptr)
            {
                m_LastError = E_FAIL;
                return false;
            }

            ComPtr<IWICBitmapDecoder> decoder;
            ComPtr<IWICBitmapFrameDecode> frame;
            ComPtr<IWICFormatConverter> converter;

            m_LastError = m_pFactory->CreateDecoderFromFilename(
                filename,
                nullptr,
                GENERIC_READ,
                WICDecodeMetadataCacheOnLoad,
                &decoder
            );

            if (FAILED(m_LastError))
                return false;

            m_LastError = decoder->GetFrame(0, &frame);

            if (FAILED(m_LastError))
                return false;

            m_LastError = m_pFactory->CreateFormatConverter(&converter);

            if (FAILED(m_LastError))
                return false;

            m_LastError = converter->Initialize(
                frame.Get(),
                GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.0f,
                WICBitmapPaletteTypeCustom
            );

            if (FAILED(m_LastError))
                return false;

            D2D1_BITMAP_PROPERTIES1 bitmapProps =
                D2D1::BitmapProperties1(
                    D2D1_BITMAP_OPTIONS_NONE,
                    D2D1::PixelFormat(
                        DXGI_FORMAT_B8G8R8A8_UNORM,
                        D2D1_ALPHA_MODE_PREMULTIPLIED
                    )
                );

            m_LastError = d2dContext->CreateBitmapFromWicBitmap(
                converter.Get(),
                bitmapProps,
                &outBitmap
            );

            if (FAILED(m_LastError))
                return false;

            return true;
        }

        bool LoadImageFromFile(__in LPCWSTR filename, __out HBITMAP& hBitmap)
        {
            hBitmap = nullptr;
            if (m_pFactory == nullptr)
            {
                m_LastError = E_FAIL;
                return false;
            }

            m_LastError = m_pFactory->CreateDecoderFromFilename(
                filename, 
                nullptr, 
                GENERIC_READ,
                WICDecodeMetadataCacheOnLoad, 
                &m_pDecoder
            );

            if (FAILED(m_LastError))
            {
                return false;
            }

            m_LastError = m_pDecoder->GetFrame(0, &m_pFrame);
            if (FAILED(m_LastError))
            {
                return false;
            }

            m_LastError = m_pFactory->CreateFormatConverter(&m_pConverter);
            if (FAILED(m_LastError))
            {
                return false;
            }

            m_LastError = m_pConverter->Initialize(m_pFrame.Get(), GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone, nullptr, 0.0f,
                WICBitmapPaletteTypeCustom);

            if (FAILED(m_LastError))
            {
                return false;
            }




            UINT width = 0, height = 0;
            m_LastError = m_pFrame->GetSize(&width, &height);

            if (FAILED(m_LastError))
            {
                return false;
            }

            BITMAPINFO bmi = { 0 };
            bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            bmi.bmiHeader.biWidth = width; // 비트맵 너비
            bmi.bmiHeader.biHeight = -static_cast<LONG>(height); // top-down DIB
            bmi.bmiHeader.biPlanes = 1; // 비트맵 평면 수
            bmi.bmiHeader.biBitCount = 32; // 32bpp
            bmi.bmiHeader.biCompression = BI_RGB; // 압축 없음

            void* pvImageBits = nullptr;
            HDC hdc = GetDC(nullptr);
            hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &pvImageBits, nullptr, 0);
            ReleaseDC(nullptr, hdc);

            if (FAILED(m_LastError))
            {
                return false;
            }

            // 비트맵에 픽셀 복사 (32bppPBGRA로 변환)
            m_LastError = m_pConverter->CopyPixels(nullptr, width * 4, width * height * 4, (BYTE*)pvImageBits);

            if (FAILED(m_LastError))
            {
                return false;
            }



            return true;
        }


        HRESULT m_LastError = S_OK;


        
        ComPtr<IWICImagingFactory> m_pFactory = nullptr;
        ComPtr<IWICBitmapDecoder> m_pDecoder = nullptr;
        ComPtr<IWICBitmapFrameDecode> m_pFrame = nullptr;
        ComPtr<IWICFormatConverter> m_pConverter = nullptr;

        WICInitializer(const WICInitializer&) = delete;
        WICInitializer& operator=(const WICInitializer&) = delete;
    }GWICInitializer;


    BitmapInfo* CreateBitmapInfo(LPCWSTR filename)
    {
        return nullptr;
    }
}