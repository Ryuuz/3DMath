#include "vector4d.h"

namespace prog {

    Vector4d::Vector4d(float a, float b, float c, float d) : x(a), y(b), z(c), w(d)
    {

    }


    //Makes a 3d vector into a 4d one
    Vector4d::Vector4d(const Vector3d &v, float d) : x(v.x), y(v.y), z(v.z), w(d)
    {

    }


    //Returns the 4d vector into a 3d one
    Vector3d Vector4d::to3d()
    {
        return Vector3d(x, y, z);
    }


    const Vector4d& Vector4d::operator=(const Vector4d &v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;

        return *this;
    }

}
