#ifndef VECTOR3D_H
#define VECTOR3D_H

namespace prog {

    class Vector3d
    {
        public:
            Vector3d(float a = 0.f, float b = 0.f, float c = 0.f);
            float length() const;
            void normalize();

            const Vector3d& operator=(const Vector3d &v);
            Vector3d operator+(const Vector3d &v) const;
            Vector3d operator-(const Vector3d &v) const;
            float operator*(const Vector3d &v) const;
            Vector3d operator*(float scale) const;
            Vector3d operator^(const Vector3d &v) const;

            float x;
            float y;
            float z;
    };

}

#endif // VECTOR3D_H
