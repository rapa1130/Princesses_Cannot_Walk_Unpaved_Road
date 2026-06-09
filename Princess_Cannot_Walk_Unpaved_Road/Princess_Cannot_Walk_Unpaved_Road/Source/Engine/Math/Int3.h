#pragma once

namespace Bisang
{

    struct Int3
    {
        int x = 0;
        int y = 0;
        int z = 0;

        Int3() = default;

        Int3(int x, int y, int z)
            : x(x), y(y), z(z)
        {
        }

        // ºñ±³
        bool operator==(const Int3& rhs) const
        {
            return x == rhs.x &&
                y == rhs.y &&
                z == rhs.z;
        }

        bool operator!=(const Int3& rhs) const
        {
            return !(*this == rhs);
        }

        // µ¡¼À
        Int3 operator+(const Int3& rhs) const
        {
            return Int3(
                x + rhs.x,
                y + rhs.y,
                z + rhs.z
            );
        }

        Int3& operator+=(const Int3& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            z += rhs.z;
            return *this;
        }

        // »¬¼À
        Int3 operator-(const Int3& rhs) const
        {
            return Int3(
                x - rhs.x,
                y - rhs.y,
                z - rhs.z
            );
        }

        Int3& operator-=(const Int3& rhs)
        {
            x -= rhs.x;
            y -= rhs.y;
            z -= rhs.z;
            return *this;
        }

        // ½ºÄ®¶ó °ö
        Int3 operator*(int scalar) const
        {
            return Int3(
                x * scalar,
                y * scalar,
                z * scalar
            );
        }

        Int3& operator*=(int scalar)
        {
            x *= scalar;
            y *= scalar;
            z *= scalar;
            return *this;
        }

        // ´ÜÇ× ºÎÈ£
        Int3 operator-() const
        {
            return Int3(
                -x,
                -y,
                -z
            );
        }
    };
}