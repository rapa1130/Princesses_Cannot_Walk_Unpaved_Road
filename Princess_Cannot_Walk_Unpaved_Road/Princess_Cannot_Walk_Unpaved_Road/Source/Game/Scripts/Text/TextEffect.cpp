#include "TextEffect.h"

#include "Engine/Object/GameObject.h"
#include "Engine/Components/TextRenderer.h"

#include <iostream>
namespace Bisang
{
	void TextEffect::Start()
	{
		m_text = m_ownerObj->GetComponent<TextRenderer>();
	}

	void TextEffect::Update(float dT)
	{
		m_time += dT;

		if (m_text != nullptr)
		{
			Color color = m_text->GetColor();
			color.a = (std::sin(m_time * 3.0f) + 1.0f) * 0.5f;
			m_text->SetColor(color);
		}
	}
}
