#pragma once

namespace Bisang
{
    inline float fClamp(float value, float min, float max)
    {
        if (value < min)
            return min;

        if (value > max)
            return max;

        return value;
    }
}

