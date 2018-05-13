#include <iostream>
#include <vector>
#include <Matrix.h>

using namespace std;

int main(int argc, char *argv[])
{
    Matrix<double> matrix(4, 4);
    // cout << matrix.getSize() << endl;
    matrix.randomize();
    // matrix.add(325.0);
    // matrix.add(1.0);
    // matrix.add(2.0);
    // matrix.add(3.0);
    matrix.print();    
    // cout << matrix.row(0) << endl;
    return 0;
}