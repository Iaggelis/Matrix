#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include "Matrix.h"
// #include "nn.h"

using namespace std;

int main(int argc, char *argv[])
{
    // NeuralNetwork brain(2, 18, 1);
    // // Matrix<double> inputs(4, 2), outputs(4, 1);
    // vector<vector<double>> inputs, outputs;
    // inputs.push_back({0, 0});
    // inputs.push_back({0, 1});
    // inputs.push_back({1, 0});
    // inputs.push_back({1, 1});

    // outputs.push_back({0});
    // outputs.push_back({1});
    // outputs.push_back({1});
    // outputs.push_back({0});

    // for (int i = 0; i < 10000; i++)
    // {
    //     for (int j = 0; j < outputs.size(); j++)
    //     {
    //         brain.train(inputs[j], outputs[j]);
    //     }
    // }

    // Matrix<double> predict = brain.predict(inputs[0]);
    // predict.print();

    // predict = brain.predict(inputs[1]);
    // predict.print();
    // Matrix<double> matrix1;
    // matrix1.copy(inputs);
    // matrix1.print();
    // function<int(int &)> ayy = [&](int &x) -> int { return x + 2; };
    // Matrix<int> matrix1(2, 2), matrix2(2, 2);
    // matrix1.randomize();
    // matrix2.randomize();
    // matrix1.print();
    // matrix2.print();

    // Matrix<int> matrix3 = Matrix<int>().subtrack(matrix1, matrix2);
    // matrix3.print();

    Matrix<double> m1(3, 4);
    m1.randomize();
    m1.print();
    m1.gaussianEllimination(m1);
    m1.print();
    return 0;
}