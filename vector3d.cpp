#include <cmath>
#include "vector3d.h"

namespace prog {

    Vector3d::Vector3d(float a, float b, float c) : x(a), y(b), z(c)
    {

    }


    //Returns the length of the vector
    float Vector3d::length() const
    {
        return sqrt(pow(x, 2.0) + pow(y, 2.0) + pow(z, 2.0));
    }


    //Normalizes the vector to make the length 1
    void Vector3d::normalize()
    {
        float len = length();
        x /= len;
        y /= len;
        z /= len;
    }


    const Vector3d& Vector3d::operator=(const Vector3d &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;

        return *this;
    }


    //Adds the xs, ys, and zs of each vector with each other's
    Vector3d Vector3d::operator+(const Vector3d &v) const
    {
        return Vector3d(x + v.x, y + v.y, z + v.z);
    }


    //Adds the xs, ys, and zs of each vector from each other's
    Vector3d Vector3d::operator-(const Vector3d &v) const
    {
        return Vector3d(x - v.x, y - v.y, z - v.z);
    }


    // Returns the dot product of the two vectors
    float Vector3d::operator*(const Vector3d &v) const
    {
        return ((x * v.x) + (y * v.y) + (z * v.z));
    }


    //Multiplies the vector with a scalar
    Vector3d Vector3d::operator*(float scale) const
    {
        return Vector3d(x * scale, y * scale, z * scale);
    }


    //Returns the cross product of the two vectors
    Vector3d Vector3d::operator^(const Vector3d &v) const
    {
        return Vector3d((y * v.z) - (z * v.y), (z * v.x) - (x * v.z), (x * v.y) - (y * v.x));
    }

}
