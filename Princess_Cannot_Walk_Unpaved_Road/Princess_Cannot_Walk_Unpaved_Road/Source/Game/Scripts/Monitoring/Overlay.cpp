#include "Overlay.h"
#include <string>
#include "Engine/Object/GameObject.h"
#include "Engine/Components/TextRenderer.h"

namespace Bisang
{
	void Overlay::Start()
	{
		m_textRenderer = m_ownerObj->GetComponent<TextRenderer>();
	}

	void Overlay::Update(float dT)
	{
		int fps = 1 / dT;
		std::wstring str = std::to_wstring(fps);
		m_textRenderer->SetText(str);
	}

	void Overlay::FixedUpdate()
	{
		// GameApp에서 설정된 고정 프레임 간격으로 호출
	}
}