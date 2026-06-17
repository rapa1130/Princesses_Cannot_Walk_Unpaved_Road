#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class TextRenderer;

	class TextEffect : public Script
	{
	public:
		TextEffect(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;

	private:
		TextRenderer* m_text = nullptr;
		float m_time = 0.0f;
	};
}