#include "ResourceManager.h"
#include"Engine/Core/Debug.h"

#include"Engine/Resource/TextResource.h"
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")

namespace Bisang
{
    bool ResourceManager::Initialize(ID2D1DeviceContext4* d2dContext)
    {
        if (d2dContext == nullptr)
        {
            DEBUG_ERROR("d2dContext is Nullptr");
            return false;
        }

        m_d2dContext = d2dContext;

        HRESULT hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&m_wicFactory)
        );

        if (FAILED(hr))
        {
            return false;
        }
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(IDWriteFactory),
            reinterpret_cast<IUnknown**>(m_dwriteFactory.GetAddressOf())
        );


        if (FAILED(hr))
        {
            DEBUG_ERROR("DWriteCreateFactory Failed");
            return false;
        }

        return true;
    }

    std::shared_ptr<TextureResource> ResourceManager::LoadTexture(
        const std::wstring& path
    )
    {
        if (auto cached = FindCached<TextureResource>(path))
        {
            return cached;
        }

        auto resource = std::make_shared<TextureResource>();

        if (!resource->LoadFromFile(
            path,
            m_wicFactory.Get(),
            m_d2dContext
        ))
        {
            return nullptr;
        }

        Cache(path, resource);
        return resource;
    }

    std::shared_ptr<TextFormatResource> ResourceManager::LoadTextFormat(
        const std::wstring& fontName,
        float fontSize
    )
    {
        std::wstring key =
            L"TextFormat:" + fontName + L":" + std::to_wstring(fontSize);

        if (auto cached = FindCached<TextFormatResource>(key))
        {
            return cached;
        }

        auto resource = std::make_shared<TextFormatResource>();

        if (!resource->CreateTextFormat(
            m_dwriteFactory.Get(),
            fontName,
            fontSize
        ))
        {
            DEBUG_ERROR("TextFormatResource Create Failed");
            return nullptr;
        }

        Cache(key, resource);
        return resource;
    }
}