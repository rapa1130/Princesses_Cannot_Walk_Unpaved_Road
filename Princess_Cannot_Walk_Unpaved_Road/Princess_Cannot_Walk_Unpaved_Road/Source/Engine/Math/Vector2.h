#pragma once

#include <cmath>

namespace Bisang
{
    struct Vector2
    {
        float x;
        float y;

        // ª˝º∫¿⁄
        Vector2()
            : x(0.0f), y(0.0f)
        {
        }

        Vector2(float _x, float _y)
            : x(_x), y(_y)
        {
        }

        operator D2D1_POINT_2F() const
        {
            D2D1_POINT_2F ret;
            ret.x = x;
            ret.y = y;
            return ret;
        }

        // ∫§≈Õ + ∫§≈Õ
        Vector2 operator+(const Vector2& rhs) const
        {
            return Vector2(x + rhs.x, y + rhs.y);
        }

        // ∫§≈Õ - ∫§≈Õ
        Vector2 operator-(const Vector2& rhs) const
        {
            return Vector2(x - rhs.x, y - rhs.y);
        }

        // ∫§≈Õ * Ω∫ƒÆ∂Û
        Vector2 operator*(float scalar) const
        {
            return Vector2(x * scalar, y * scalar);
        }

        // ∫§≈Õ / Ω∫ƒÆ∂Û
        Vector2 operator/(float scalar) const
        {
            return Vector2(x / scalar, y / scalar);
        }

        // +=
        Vector2& operator+=(const Vector2& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        // -=
        Vector2& operator-=(const Vector2& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        // *=
        Vector2& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        // /=
        Vector2& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        // == ∫Ò±≥
        bool operator==(const Vector2& rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }

        // != ∫Ò±≥
        bool operator!=(const Vector2& rhs) const
        {
            return !(*this == rhs);
        }

        // ∫§≈Õ ±Ê¿Ã
        float Length() const
        {
            return std::sqrt(x * x + y * y);
        }

        // ¡§±‘»≠
        Vector2 Normalize() const
        {
            float len = Length();

            if (len == 0.0f)
                return Vector2();

            return Vector2(x / len, y / len);
        }

        // ≥ª¿˚
        static float Dot(const Vector2& a, const Vector2& b)
        {
            return a.x * b.x + a.y * b.y;
        }
    };
}