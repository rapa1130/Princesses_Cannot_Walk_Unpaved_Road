#include "TextResource.h"
#include "Engine/Core/Debug.h"

bool Bisang::TextFormatResource::CreateTextFormat(
                                        IDWriteFactory* dwriteFactory, 
                                        const std::wstring& fontName, 
                                        float fontSize)
{
    if (dwriteFactory == nullptr)
        return false;

    HRESULT hr = dwriteFactory->CreateTextFormat(
        fontName.c_str(),
        nullptr,
        DWRITE_FONT_WEIGHT_NORMAL,
        DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL,
        fontSize,
        L"ko-kr",
        m_textFormat.GetAddressOf()
    );

    if (FAILED(hr))
        return false;

    m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
    m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

    return true;
}
