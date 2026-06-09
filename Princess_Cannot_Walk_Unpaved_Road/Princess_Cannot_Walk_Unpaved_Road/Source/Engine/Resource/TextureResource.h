#pragma once

#include "Engine/Resource/IResource.h"
#include "Engine/Renderer/DxHeaders.h"
#include "Engine/Math/Vector.h"
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

        const Vector3& GetPivot() const { return m_pivot; }
        void SetPivot(const Vector3& pivot) { m_pivot = pivot; }

    private:
        ComPtr<ID2D1Bitmap1> m_bitmap;
        Vector3 m_pivot;
    };
}