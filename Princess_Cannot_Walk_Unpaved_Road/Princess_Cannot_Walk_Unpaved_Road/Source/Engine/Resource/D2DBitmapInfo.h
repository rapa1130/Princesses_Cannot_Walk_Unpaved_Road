#pragma once

#include <wrl/client.h>
#include <d2d1_1.h>

namespace Bisang
{
    struct WICInitializer;
    class DxBitmapInfo
    {
    public:
        ID2D1Bitmap1* GetBitmapHandle() const { return m_bitmap.Get(); }
        int GetWidth() const { return m_bitmap->GetSize().width; }
        int GetHeight() const { return m_bitmap->GetSize().height; }

    private:
        friend struct WICInitializer;

        DxBitmapInfo() = default;

        DxBitmapInfo(Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap)
            : m_bitmap(bitmap)
        {

        }

    private:
        Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;

        DxBitmapInfo(const DxBitmapInfo&) = delete;
        DxBitmapInfo& operator=(const DxBitmapInfo&) = delete;
    };

    DxBitmapInfo* CreateBitmapInfo(ID2D1DeviceContext* d2dDC, LPCWSTR filename);
}