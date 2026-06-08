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


    struct Vector3
    {
        float x;
        float y;
        float z;

        // ª˝º∫¿⁄
        Vector3()
            : x(0.0f), y(0.0f), z(0.0f)
        {
        }

        Vector3(float _x, float _y, float _z)
            : x(_x), y(_y), z(_z)
        {
        }

        // ∫§≈Õ + ∫§≈Õ
        Vector3 operator+(const Vector3& rhs) const
        {
            return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        // ∫§≈Õ - ∫§≈Õ
        Vector3 operator-(const Vector3& rhs) const
        {
            return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        // ∫§≈Õ * Ω∫ƒÆ∂Û
        Vector3 operator*(float scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        // ∫§≈Õ / Ω∫ƒÆ∂Û
        Vector3 operator/(float scalar) const
        {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }

        // +=
        Vector3& operator+=(const Vector3& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        // -=
        Vector3& operator-=(const Vector3& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        // *=
        Vector3& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        // /=
        Vector3& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        // == ∫Ò±≥
        bool operator==(const Vector3& rhs) const
        {
            return x == rhs.x &&
                y == rhs.y &&
                z == rhs.z;
        }

        // != ∫Ò±≥
        bool operator!=(const Vector3& rhs) const
        {
            return !(*this == rhs);
        }

        // ∫§≈Õ ±Ê¿Ã
        float Length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        // ¡§±‘»≠
        Vector3 Normalize() const
        {
            float len = Length();

            if (len == 0.0f)
                return Vector3();

            return Vector3(
                x / len,
                y / len,
                z / len
            );
        }

        // ≥ª¿˚
        static float Dot(const Vector3& a, const Vector3& b)
        {
            return a.x * b.x +
                a.y * b.y +
                a.z * b.z;
        }

        // ø‹¿˚
        static Vector3 Cross(const Vector3& a, const Vector3& b)
        {
            return Vector3(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            );
        }
    };
}