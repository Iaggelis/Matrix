#pragma once

#include <vector>
#include <cmath>
#include <functional>
#include "Matrix.h"

std::function<double(double &)> sigmoid = [&](double &x) { return 1 / (1 + std::exp(-x)); };
std::function<double(double &)> dsigmoid = [&](double &x) { return 1 - (1 - x); };

std::function<double(double &)> mytanh = [&](double &x) { return std::tanh(x); };
std::function<double(double &)> dtanh = [&](double &x) { return 1 - (x * x); };

class NeuralNetwork
{
  private:
    Matrix<double> inputs, hidden, output;
    int input_nodes, hidden_nodes, output_nodes;

    Matrix<double> weights_ih, weights_ho;
    Matrix<double> bias_h, bias_o; // (rows,1)

    double learning_rate;
    std::vector<std::pair<std::function<double(double &)>, std::function<double(double &)>>> functions;
    std::pair<std::function<double(double &)>, std::function<double(double &)>> activation_function;

  public:
    NeuralNetwork(int a, int b, int c)
        : input_nodes(a), hidden_nodes(b), output_nodes(c)
    {
        weights_ih = Matrix<double>(hidden_nodes, input_nodes);
        weights_ho = Matrix<double>(output_nodes, hidden_nodes);

        weights_ih.randomize();
        weights_ho.randomize();
        functions.emplace_back(sigmoid, dsigmoid);
        functions.emplace_back(mytanh, dtanh);

        setLearningRate();
        setActivationFunction(functions[0]);
    }

    void setActivationFunction(std::pair<std::function<double(double &)>, std::function<double(double &)>> &activ_func)
    {
        activation_function = activ_func;
    }

    void setLearningRate(double lrate = 0.1)
    {
        learning_rate = lrate;
    }

    Matrix<double> predict(Matrix<double> &input_array) {
        inputs = input_array;
        hidden = Matrix<double>().multiply(weights_ih,inputs);
    }
};
