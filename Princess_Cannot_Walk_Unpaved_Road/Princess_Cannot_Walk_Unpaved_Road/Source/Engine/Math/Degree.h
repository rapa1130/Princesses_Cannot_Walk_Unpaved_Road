#pragma once

namespace Bisang
{
	constexpr float PI = 3.14159265358979323846f;

	inline float DegToRad(float degree)
	{
		return degree * PI / 180.0f;
	}
}