#include "SampleScript.h"

namespace Bisang
{
	void SampleScript::Start()
	{
		// update() 호출 전 최초 1회 호출
	}

	void SampleScript::Update(float dT)
	{
		// dT 간격으로 호출
	}

	void SampleScript::FixedUpdate()
	{
		// GameApp에서 설정된 고정 프레임 간격으로 호출
	}
}