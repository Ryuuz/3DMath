#include <iostream>
#include "matrix4d.h"

using namespace std;

int main()
{
    prog::Matrix4d mat1(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0, 12.0, 13.0, 14.0, 15.0, 16.0);
    prog::Matrix4d mat2 = mat1.inverseMatrix();

    int i = 0;
    for(auto element : mat2.matrix)
    {
        if(i%4 == 0) cout << endl;

        cout << element << ", ";
        i++;
    }

    cout << endl << endl;

    return 0;
}
