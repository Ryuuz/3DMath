#ifndef MATRIX4D_H
#define MATRIX4D_H

#include <array>
#include "vector4d.h"

namespace prog {

    class Matrix4d
    {
        public:
            Matrix4d(float a = 0.f, float b = 0.f, float c = 0.f, float d = 0.f,
                     float e = 0.f, float f = 0.f, float g = 0.f, float h = 0.f,
                     float i = 0.f, float j = 0.f, float k = 0.f, float l = 0.f,
                     float m = 0.f, float n = 0.f, float o = 0.f, float p = 0.f);
            Matrix4d(std::array<float, 4*4> &m);
            void identityMatrix();
            void scale(float x = 1.0, float y = 1.0, float z = 1.0);
            void rotate(float angle, const Vector3d &axis);
            void translate(float x = 0.0, float y = 0.0, float z = 0.0);
//            Matrix4d projectionMatrix();
            Matrix4d inverseMatrix();

            Matrix4d operator*(float scale);
            Vector4d operator*(const Vector4d &v);
            Matrix4d operator*(const Matrix4d &m);
            const Matrix4d& operator=(const Matrix4d &m);

            std::array<float, (4*4)> matrix;
    };

}

#endif // MATRIX4D_H
