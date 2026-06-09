#pragma once

#include <cmath>

namespace Bisang
{
    struct Vector3;

    struct Vector2
    {
        float x;
        float y;

        Vector2()
            : x(0.0f), y(0.0f)
        {
        }

        Vector2(float _x, float _y)
            : x(_x), y(_y)
        {
        }

        Vector2(const Vector3& v);

        Vector2 operator+(const Vector2& rhs) const
        {
            return Vector2(x + rhs.x, y + rhs.y);
        }

        Vector2 operator-(const Vector2& rhs) const
        {
            return Vector2(x - rhs.x, y - rhs.y);
        }

        Vector2 operator*(float scalar) const
        {
            return Vector2(x * scalar, y * scalar);
        }

        Vector2 operator/(float scalar) const
        {
            return Vector2(x / scalar, y / scalar);
        }

        Vector2& operator+=(const Vector2& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Vector2& operator-=(const Vector2& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        Vector2& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            return *this;
        }

        Vector2& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            return *this;
        }

        bool operator==(const Vector2& rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }

        bool operator!=(const Vector2& rhs) const
        {
            return !(*this == rhs);
        }

        float Length() const
        {
            return std::sqrt(x * x + y * y);
        }

        Vector2 Normalize() const
        {
            float len = Length();

            if (len == 0.0f)
                return Vector2();

            return Vector2(x / len, y / len);
        }

        static float Dot(const Vector2& a, const Vector2& b)
        {
            return a.x * b.x + a.y * b.y;
        }

        static Vector2 Rotate2D(const Vector2& v, float rad)
        {
            float c = cosf(rad);
            float s = sinf(rad);

            return Vector2(
                v.x * c - v.y * s,
                v.x * s + v.y * c
            );
        }
    };

    struct Vector3
    {
        float x;
        float y;
        float z;

        Vector3()
            : x(0.0f), y(0.0f), z(0.0f)
        {
        }

        Vector3(float _x, float _y, float _z)
            : x(_x), y(_y), z(_z)
        {
        }

        Vector3(const Vector2& v)
            : x(v.x), y(v.y), z(0.0f)
        {
        }

        Vector3 operator+(const Vector3& rhs) const
        {
            return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
        }

        Vector3 operator-(const Vector3& rhs) const
        {
            return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
        }

        Vector3 operator*(float scalar) const
        {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }

        Vector3 operator/(float scalar) const
        {
            return Vector3(x / scalar, y / scalar, z / scalar);
        }

        Vector3& operator+=(const Vector3& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        Vector3& operator-=(const Vector3& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        Vector3& operator*=(float scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        Vector3& operator/=(float scalar)
        {
            x /= scalar;
            y /= scalar;
            z /= scalar;
            return *this;
        }

        bool operator==(const Vector3& rhs) const
        {
            return x == rhs.x &&
                y == rhs.y &&
                z == rhs.z;
        }

        bool operator!=(const Vector3& rhs) const
        {
            return !(*this == rhs);
        }

        float Length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

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

        static float Dot(const Vector3& a, const Vector3& b)
        {
            return a.x * b.x +
                a.y * b.y +
                a.z * b.z;
        }

        static Vector3 Cross(const Vector3& a, const Vector3& b)
        {
            return Vector3(
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            );
        }
    };

    inline Vector2::Vector2(const Vector3& v)
        : x(v.x), y(v.y)
    {
    }
}