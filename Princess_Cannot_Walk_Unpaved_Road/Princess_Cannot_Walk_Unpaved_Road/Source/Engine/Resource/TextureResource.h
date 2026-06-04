#pragma once

#include "Engine/Resource/IResource.h"
#include "Engine/Renderer/DxHeaders.h"

#include <string>

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