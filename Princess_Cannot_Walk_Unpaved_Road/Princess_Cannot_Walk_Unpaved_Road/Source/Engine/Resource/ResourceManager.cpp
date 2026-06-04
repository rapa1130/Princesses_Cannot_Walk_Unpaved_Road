#include "ResourceManager.h"



namespace Bisang
{
    bool ResourceManager::Initialize()
    {
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

        return true;
    }

    std::shared_ptr<TextureResource> ResourceManager::LoadTexture(
        const std::wstring& path,
        ID2D1DeviceContext4* d2dContext
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
            d2dContext
        ))
        {
            return nullptr;
        }

        Cache(path, resource);
        return resource;
    }
}