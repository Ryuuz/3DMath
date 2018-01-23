#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "vector3d.h"

namespace prog {

    class Vector4d
    {
        public:
            Vector4d(float a = 0.f, float b = 0.f, float c = 0.f, float d = 1.f);
            Vector4d(const Vector3d &v, float d = 1.f);
            Vector3d to3d();

            const Vector4d& operator=(const Vector4d &v);

            float x;
            float y;
            float z;
            float w;
    };

}

#endif // VECTOR4D_H
