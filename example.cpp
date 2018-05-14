#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include "Matrix.h"
#include "nn.h"

using namespace std;

int main(int argc, char *argv[])
{
    // function<int(int &)> ayy = [&](int &x) -> int { return x + 2; };
    // Matrix<int> matrix1(2, 2);
    // matrix1.randomize();
    // matrix1.print();
    // Matrix<int> matrix3 = matrix1.copy();
    // matrix3.print();
    // matrix3.map(ayy);
    // matrix3.print();

    NeuralNetwork brain(2, 3, 1);
    return 0;
}