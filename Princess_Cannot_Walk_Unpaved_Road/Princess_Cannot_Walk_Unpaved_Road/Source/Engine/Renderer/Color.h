#pragma once
#include"d2d1.h"

namespace Bisang
{
	struct Color
	{
		float r;
		float g;
		float b;
		float a;

		Color()
			:r(0), g(0), b(0), a(0) {
		}
		Color(float r, float g, float b, float a)
			:r(r), g(g), b(b), a(a) {
		}

		operator D2D1_COLOR_F() const
		{
			D2D1_COLOR_F ret;
			ret.a = a;
			ret.r = r;
			ret.g = g;
			ret.b = b;
			return ret;
		}


	};

}