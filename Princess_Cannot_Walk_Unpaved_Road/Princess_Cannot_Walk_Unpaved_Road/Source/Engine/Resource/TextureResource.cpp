#include "TextureResource.h"

namespace Bisang
{
    bool TextureResource::LoadFromFile(
        const std::wstring& path,
        IWICImagingFactory* wicFactory,
        ID2D1DeviceContext4* d2dContext
    )
    {
        if (wicFactory == nullptr || d2dContext == nullptr)
        {
            return false;
        }

        ComPtr<IWICBitmapDecoder> decoder;
        HRESULT hr = wicFactory->CreateDecoderFromFilename(
            path.c_str(),
            nullptr,
            GENERIC_READ,
            WICDecodeMetadataCacheOnLoad,
            &decoder
        );

        if (FAILED(hr))
        {
            return false;
        }

        ComPtr<IWICBitmapFrameDecode> frame;
        hr = decoder->GetFrame(0, &frame);

        if (FAILED(hr))
        {
            return false;
        }

        ComPtr<IWICFormatConverter> converter;
        hr = wicFactory->CreateFormatConverter(&converter);

        if (FAILED(hr))
        {
            return false;
        }

        hr = converter->Initialize(
            frame.Get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0f,
            WICBitmapPaletteTypeMedianCut
        );

        if (FAILED(hr))
        {
            return false;
        }

        hr = d2dContext->CreateBitmapFromWicBitmap(
            converter.Get(),
            nullptr,
            &m_bitmap
        );

        if (FAILED(hr))
        {
            return false;
        }

        return true;
    }
}