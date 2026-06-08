#include"Engine/Components/TextRenderer.h"
#include<string>
#include"Engine/Resource/TextResource.h"
#include"Engine/Core/Debug.h"
#include"Engine/Object/GameObject.h"
#include"Engine/Components/Transform.h"
#include"Engine/Renderer/RenderCommand.h"
#include"Engine/Renderer/Renderer.h"

namespace Bisang
{
    TextRenderer::TextRenderer(GameObject* ownerObj, Scene* scene) :
        RenderableComponent(ownerObj,scene)
    {
        m_color = Bisang::Color::Green;
    }

    void TextRenderer::DrawCall(Renderer* renderer)
	{
        if (m_text.empty()) return;
        if (m_transform == nullptr)
        {
            DEBUG_ERROR_LOCATION("transform is nullptr");
            return;
        }
        if (m_textFormat == nullptr)
        {
            SetTextFormat(L"Malgun Gothic", 12.0f);
        }

        RenderCommand rc = RenderCommand::CreateTextRC(
            m_text.c_str(),
            static_cast<UINT32>(m_text.length()),
            m_textFormat.get(),
            m_transform->GetPosition(),
            m_transform->GetScale(),
            m_color,
            GetLayer()
        );


        renderer->Submit(rc);
	}



    //Getters
    std::wstring TextRenderer::GetText() const
    {
        return m_text;
    }
    Bisang::Color TextRenderer::GetColor() const 
    {
        return m_color;
    }
    std::wstring TextRenderer::GetFontName() const
    {
        if (m_textFormat == nullptr || m_textFormat->GetTextFormat() == nullptr)
            return L"";

        IDWriteTextFormat* format = m_textFormat->GetTextFormat();

        UINT32 length = format->GetFontFamilyNameLength();

        std::wstring fontName;
        fontName.resize(length + 1);

        HRESULT hr = format->GetFontFamilyName(
            &fontName[0],
            length + 1
        );

        if (FAILED(hr))
            return L"";

        fontName.resize(length);

        return fontName;
    }
    float TextRenderer::GetFontSize() const
    {
        if (m_textFormat == nullptr || m_textFormat->GetTextFormat() == nullptr)
            return 0.0f;

        return m_textFormat->GetTextFormat()->GetFontSize();
    }

    //Setters
    void TextRenderer::SetTextFormat(std::wstring fontName, float fontSize)
    {
        ResourceManager* resourceManager = GetResourceManager();

        if (resourceManager == nullptr)
        {
            DEBUG_ERROR_LOCATION("resourceManager is nullptr");
            return;
        }

        m_textFormat = resourceManager->LoadTextFormat(fontName, fontSize);

        if (m_textFormat == nullptr)
        {
            DEBUG_ERROR_LOCATION("fail to load text foramt");
            return;
        }
    }
    void TextRenderer::SetText(const std::wstring& text)
    {
        m_text = text;
    }
    void TextRenderer::SetColor(const Bisang::Color& color)
    {
        m_color = color;
    }



}