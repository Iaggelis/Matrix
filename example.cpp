#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include "Matrix.h"
#include "nn.h"

using namespace std;

int main(int argc, char *argv[])
{
    Matrix<int> matrix1(2, 2), matrix2(2, 2);
    // cout << matrix.getSize() << endl;
    matrix1.randomize();
    matrix1.print();
    // matrix2.print();

    function<int(int &)> ayy = [&](int &x) -> int { return x + 2; };
    Matrix<int> matrix3 = matrix1.copy();
    // matrix3.print();
    // matrix3.transpose();
    matrix3.map(ayy);
    matrix3.print();

    Matrix<int> matrix4(2, 2);
    // matrix4 = matrix4.multiply(matrix1, matrix3);
    matrix4 = Matrix<int>(2, 2).multiply(matrix1, matrix3);
    matrix4.print();
    return 0;
}