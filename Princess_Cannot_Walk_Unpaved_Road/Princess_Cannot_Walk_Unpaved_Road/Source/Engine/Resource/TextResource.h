#pragma once

#include"Engine/Renderer/DxHeaders.h"
#include <string>
#include"Engine/Resource/IResource.h"


namespace Bisang
{
    class TextFormatResource : public IResource
    {
    public:
        bool CreateTextFormat(
            IDWriteFactory* dwriteFactory,
            const std::wstring& fontName,
            float fontSize
        );

        IDWriteTextFormat* GetTextFormat() const
        {
            return m_textFormat.Get();
        }

    private:
        ComPtr<IDWriteTextFormat> m_textFormat;
    };
}

/*



namespace Bisang
{
    class TextureResource : public IResource
    {
    public:
        bool LoadFromFile(
            const std::wstring& path,
            IWICImagingFactory* wicFactory,
            ID2D1DeviceContext4* d2dContext
        );

        ID2D1Bitmap1* GetBitmap() const
        {
            return m_bitmap.Get();
        }

    private:
        ComPtr<ID2D1Bitmap1> m_bitmap;
    };
}



*/