#pragma once
#include "Engine/Components/Script.h"

namespace Bisang
{
	class TextRenderer;

	class Overlay : public Script
	{
	public:
		Overlay(GameObject* ownerObj) : Script(ownerObj) {}

		void Start() override;
		void Update(float dT) override;
		void FixedUpdate() override;

	private:
		TextRenderer* m_textRenderer;
	};
}
