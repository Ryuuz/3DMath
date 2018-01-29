#define _USE_MATH_DEFINES
#include <cmath>
#include <utility>
#include <iostream>
#include "matrix4d.h"

namespace prog {

    Matrix4d::Matrix4d(float a, float b, float c, float d,
                       float e, float f, float g, float h,
                       float i, float j, float k, float l,
                       float m, float n, float o, float p)
    {
        matrix = {a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p};
    }


    Matrix4d::Matrix4d(std::array<float, 4*4> &m) : matrix(m)
    {

    }


    //Sets the matrix to the identity matrix
    void Matrix4d::identityMatrix()
    {
        matrix.fill(0);

        matrix.at(0) = 1.f;
        matrix.at(5) = 1.f;
        matrix.at(10) = 1.f;
        matrix.at(15) = 1.f;
    }


    //Makes the matrix into a scaling matrix
    void Matrix4d::scale(float x, float y, float z)
    {
        identityMatrix();
        matrix.at(0) = x;
        matrix.at(5) = y;
        matrix.at(10) = z;
    }


    //Makes the matrix into a rotation matrix that rotates 'angle' degrees around the given axis
    void Matrix4d::rotate(float angle, const Vector3d &axis)
    {
        identityMatrix();

        if(axis.x > 0 && axis.y == 0 && axis.z == 0)
        {
            matrix.at(5) = cos(angle*(M_PI/180.f));
            matrix.at(6) = -sin(angle*(M_PI/180.f));
            matrix.at(9) = sin(angle*(M_PI/180.f));
            matrix.at(10) = cos(angle*(M_PI/180.f));
        }
        else if(axis.x == 0 && axis.y > 0 && axis.z == 0)
        {
            matrix.at(0) = cos(angle*(M_PI/180.f));
            matrix.at(2) = sin(angle*(M_PI/180.f));
            matrix.at(8) = -sin(angle*(M_PI/180.f));
            matrix.at(10) = cos(angle*(M_PI/180.f));
        }
        else if(axis.x == 0 && axis.y == 0 && axis.z > 0)
        {
            matrix.at(0) = cos(angle*(M_PI/180.f));
            matrix.at(1) = -sin(angle*(M_PI/180.f));
            matrix.at(4) = sin(angle*(M_PI/180.f));
            matrix.at(5) = cos(angle*(M_PI/180.f));
        }
    }


    //Makes the matrix into a translation matrix
    void Matrix4d::translate(float x, float y, float z)
    {
        identityMatrix();
        matrix.at(3) = x;
        matrix.at(7) = y;
        matrix.at(11) = z;
    }


    //Finds the projection matrix
    Matrix4d Matrix4d::projectionMatrix(float fov, float aspect, float near, float far)
        {
            //Calculate all the sides of the frustum
            float top = tan(fov/2)*near;
            float bottom = -top;
            float right = top*aspect;
            float left = -right;

            Matrix4d proj;

            //Create the projection matrix
            proj.matrix.at(0) = (2*near)/(right-left);
            proj.matrix.at(2) = (right+left)/(right-left);
            proj.matrix.at(5) = (2*near)/(top-bottom);
            proj.matrix.at(6) = (top+bottom)/(top-bottom);
            proj.matrix.at(10) = -(far+near)/(far-near);
            proj.matrix.at(11) = -(2*near*far)/(far-near);
            proj.matrix.at(14) = -1;

            return proj;
        }

    //Returns the inverse of the matrix if there is one
    Matrix4d Matrix4d::inverseMatrix()
    {
        Matrix4d id;
        id.identityMatrix();
        std::array<float, 4*4> tempMat = matrix;

        //Go through each column
        for(int i = 0; i < 4; i++)
        {
            //No inverse of the matrix if only 0s in a row
            for(int r = 0; r < 4; r++)
            {
                bool zeros = true;
                for(int c = r*4; c < (r*4)+4; c++)
                {
                    if(tempMat.at(c) != 0.f)
                    {
                        zeros = false;
                    }
                }

                if(zeros)
                {
                    std::cout << "no inverse" << std::endl;
                    return id;
                }
            }

            float maxValue = tempMat.at((i*4)+i);
            int row = i;

            //Find the max value in the column
            for(int j = ((i+1)*4)+i; j < 4*4; j += 4)
            {
                if(std::abs(tempMat.at(j)) > std::abs(maxValue))
                {
                    maxValue = tempMat.at(j);
                    row = j/4;
                }
            }

            //No inverse if column only has zeros
            if(maxValue == 0.f)
            {
                std::cout << "no inverse" << std::endl;
                return id;
            }

            //If the row with the highest value is a different row that the current one
            if(row != i)
            {
                //Swap the two rows
                for(int k = i*4; k < (i*4)+4; k++)
                {
                    std::swap(tempMat.at(k), tempMat.at((row*4)+(k%4)));
                    std::swap(id.matrix.at(k), id.matrix.at((row*4)+(k%4)));
                }
            }

            //Divide all numbers in the row with the value to get 1 at i
            for(int k = i*4; k < (i*4)+4; k++)
            {
                tempMat.at(k) *= (1/maxValue);
                id.matrix.at(k) *= (1/maxValue);
            }

            float multiple = 0.f;

            //Goes to each row
            for(int k = 0; k < 4*4; k+=4)
            {
                //If the row is not i
                if(k/4 != i)
                {
                    //Get the value of the element in the same column as i
                    multiple = -tempMat.at(k+i);

                    //Go through each element in the row and subtract i*multiple from them
                    for(int l = k; l < k+4; l++)
                    {
                        tempMat.at(l) += tempMat.at((i*4)+(l%4))*multiple;
                        id.matrix.at(l) += id.matrix.at((i*4)+(l%4))*multiple;
                    }
                }            
            }
        }

        return Matrix4d(tempMat);
    }


    //Multiplies the matrix with a scalar
    Matrix4d Matrix4d::operator*(float scale)
    {
        Matrix4d temp;

        for(unsigned int i = 0; i < matrix.size(); i++)
        {
            temp.matrix.at(i) = matrix.at(i)*scale;
        }

        return temp;
    }


    //Multiplies the matrix with a vector and returning the resulting vector
    Vector4d Matrix4d::operator*(const Vector4d &v)
    {
        std::array<float, 4> temp;

        for(int i = 0; i < matrix.size(); i += 4)
        {
            temp[i/4] = (matrix.at(i)*v.x) + (matrix.at(i+1)*v.y) + (matrix.at(i+2)*v.z) + (matrix.at(i+3)*v.w);
        }

        return Vector4d(temp.at(0), temp.at(1), temp.at(2), temp.at(3));
    }


    //Returns the resulting matrix after multiplying two matrices
    Matrix4d Matrix4d::operator*(const Matrix4d &m)
    {
        Matrix4d temp;

        //Goes through all the indices, one row at a time
        for(int i = 0; i < matrix.size(); i++)
        {
            //Finds the index matrix m will start at
            int index = (i%4)*4;

            //Goes through all 4 columns in the row defined by index
            for(int j = index; j < (index + 4); j++)
            {
                temp.matrix.at((j%4)+(4*(i/4))) += matrix.at(i) * m.matrix.at(j);
            }
        }

        return temp;
    }


    const Matrix4d& Matrix4d::operator=(const Matrix4d &m)
    {
        for(int i = 0; i < matrix.size(); i++)
        {
            matrix.at(i) = m.matrix.at(i);
        }

        return *this;
    }

}
