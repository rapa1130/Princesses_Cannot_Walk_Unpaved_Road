#pragma once
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <math.h>
#include"Engine/Math/Vector.h"
#include"Engine/Math/Math.h"


namespace Bisang
{
    class PerlinNoise2D
    {
    public:
        PerlinNoise2D(int gridWidth, int gridHeight, unsigned int seed)
            : m_gridWidth(gridWidth),
            m_gridHeight(gridHeight)
        {
            m_gradients.resize(m_gridWidth * m_gridHeight);

            std::mt19937 rng(seed);
            std::uniform_real_distribution<float> angleDist(0.0f, 6.28318530718f);

            for (int y = 0; y < m_gridHeight; ++y)
            {
                for (int x = 0; x < m_gridWidth; ++x)
                {
                    float angle = angleDist(rng);

                    Vector2 dir;
                    dir.x = std::cos(angle);
                    dir.y = std::sin(angle);

                    m_gradients[y * m_gridWidth + x] = dir;
                }
            }
        }

        float Noise(float x, float y) const
        {
            int x0 = static_cast<int>(std::floor(x));
            int y0 = static_cast<int>(std::floor(y));

            int x1 = x0 + 1;
            int y1 = y0 + 1;

            float localX = x - static_cast<float>(x0);
            float localY = y - static_cast<float>(y0);

            Vector2 g00 = GetGradient(x0, y0);
            Vector2 g10 = GetGradient(x1, y0);
            Vector2 g01 = GetGradient(x0, y1);
            Vector2 g11 = GetGradient(x1, y1);

            float n00 = DotGridGradient(g00, x - x0, y - y0);
            float n10 = DotGridGradient(g10, x - x1, y - y0);
            float n01 = DotGridGradient(g01, x - x0, y - y1);
            float n11 = DotGridGradient(g11, x - x1, y - y1);

            float u = Fade(localX);
            float v = Fade(localY);

            float ix0 = Lerp(n00, n10, u);
            float ix1 = Lerp(n01, n11, u);

            float value = Lerp(ix0, ix1, v);

            // 대략 -1~1 근처 값을 0~1로 변환
            return fClamp(value * 0.5f + 0.5f, 0.0f, 1.0f);
        }

        float FractalNoise(float x, float y, int octaveCount, float persistence = 0.5f, float lacunarity = 2.0f) const
        {
            float total = 0.0f;
            float amplitude = 1.0f;
            float frequency = 1.0f;
            float maxAmplitude = 0.0f;

            for (int i = 0; i < octaveCount; ++i)
            {
                total += Noise(x * frequency, y * frequency) * amplitude;

                maxAmplitude += amplitude;
                amplitude *= persistence;
                frequency *= lacunarity;
            }

            if (maxAmplitude <= 0.0f)
                return 0.0f;

            return total / maxAmplitude;
        }

    private:
        int m_gridWidth = 0;
        int m_gridHeight = 0;
        std::vector<Vector2> m_gradients;

    private:
        Vector2 GetGradient(int x, int y) const
        {
            // 간단 버전: 범위 밖은 clamp
            x = fClamp(x, 0, m_gridWidth - 1);
            y = fClamp(y, 0, m_gridHeight - 1);

            return m_gradients[y * m_gridWidth + x];
        }

        static float DotGridGradient(const Vector2& gradient, float dx, float dy)
        {
            return gradient.x * dx + gradient.y * dy;
        }

        static float Fade(float t)
        {
            // Ken Perlin's smootherstep: 6t^5 - 15t^4 + 10t^3
            return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
        }

        static float Lerp(float a, float b, float t)
        {
            return a + t * (b - a);
        }
    };
}