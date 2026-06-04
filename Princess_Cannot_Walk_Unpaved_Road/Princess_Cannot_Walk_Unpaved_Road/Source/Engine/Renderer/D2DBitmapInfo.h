#pragma once

#include <wrl/client.h>
#include <d2d1_1.h>

namespace Bisang
{
    struct WICInitializer;
    class BitmapInfo
    {
    public:
        ID2D1Bitmap1* GetBitmapHandle() const { return m_bitmap.Get(); }
        int GetWidth() const { return m_width; }
        int GetHeight() const { return m_height; }

    private:
        friend struct WICInitializer;

        BitmapInfo() = default;

        BitmapInfo(
            Microsoft::WRL::ComPtr<ID2D1Bitmap1> bitmap,
            int width,
            int height)
            : m_bitmap(bitmap)
            , m_width(width)
            , m_height(height)
        {
        }

    private:
        Microsoft::WRL::ComPtr<ID2D1Bitmap1> m_bitmap;

        int m_width = 0;
        int m_height = 0;

        BitmapInfo(const BitmapInfo&) = delete;
        BitmapInfo& operator=(const BitmapInfo&) = delete;
    };

    BitmapInfo* CreateBitmapInfo(LPCWSTR filename);
}