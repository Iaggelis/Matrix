#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include "Matrix.h"

using namespace std;

int main(int argc, char *argv[])
{
    Matrix<double> matrix1(3, 2), matrix2(2, 2);
    // cout << matrix.getSize() << endl;
    matrix1.randomize();
    matrix2.randomize();
    matrix1.print();
    // matrix2.print();
    cout << '\n';

    function<double(double)> ayy = [&](double x) -> double { return x * 2; };
    Matrix<double> matrix3 = matrix1.copy();
    // matrix3.print();
    // matrix3.transpose();
    matrix3.map(ayy);
    matrix3.print();
    // matrix3 = matrix1.copy();

    return 0;
}