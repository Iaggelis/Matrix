#pragma once

#include <vector>
#include <cmath>
#include <chrono>
#include <random>
#include <functional>
#include "Matrix.h"

std::function<double(double &)> sigmoid = [&](double &x) { return 1.0 / (1.0 + std::exp(-x)); };
std::function<double(double &)> dsigmoid = [&](double &x) { return 1.0 * (1.0 - x); };

std::function<double(double &)> mytanh = [&](double &x) { return std::tanh(x); };
std::function<double(double &)> dtanh = [&](double &x) { return 1.0 - (x * x); };

class NeuralNetwork
{
  private:
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
        weights_ih.copy(Matrix<double>(hidden_nodes, input_nodes));
        weights_ho.copy(Matrix<double>(output_nodes, hidden_nodes));

        weights_ih.randomize();
        weights_ho.randomize();

        functions.emplace_back(sigmoid, dsigmoid);
        functions.emplace_back(mytanh, dtanh);

        bias_h.copy(Matrix<double>(hidden_nodes, 1));
        bias_o.copy(Matrix<double>(output_nodes, 1));
        bias_h.randomize();
        bias_o.randomize();

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

    Matrix<double> predict(std::vector<double> &input_array)
    {
        Matrix<double> inputs, hidden, output;
        inputs.fromVector(input_array);
        hidden.copy(Matrix<double>().multiply(weights_ih, inputs));
        hidden.add(bias_h);
        hidden.map(activation_function.first);

        output.copy(Matrix<double>().multiply(weights_ho, hidden));

        output.add(bias_o);
        output.map(activation_function.first);
        return output;
    }

    void train(std::vector<double> &input_array, std::vector<double> &target_array)
    {
        // Hidden layer outputs
        Matrix<double> inputs, hidden, output;
        inputs.fromVector(input_array);
        hidden.copy(Matrix<double>().multiply(weights_ih, inputs));
        hidden.add(bias_h);
        hidden.map(activation_function.first);
        // Output's output
        output.copy(Matrix<double>().multiply(weights_ho, hidden));
        output.add(bias_o);
        output.map(activation_function.first);

        Matrix<double> targets, output_errors, gradients;
        targets.fromVector(target_array);

        // Calculate error
        output_errors.copy(Matrix<double>().subtrack(targets, output));

        // Calculate gradient
        gradients.copy(Matrix<double>().map(output, activation_function.second));
        gradients.multiply(output_errors);
        gradients.multiply(learning_rate);

        // Calculate deltas
        Matrix<double> hidden_T = Matrix<double>().transpose(hidden);
        Matrix<double> weights_ho_deltas = Matrix<double>().multiply(gradients, hidden_T);

        weights_ho.add(weights_ho_deltas);
        bias_o.add(gradients);

        // hidden layer errors
        Matrix<double> who_T = Matrix<double>().transpose(weights_ho);
        Matrix<double> hidden_errors = Matrix<double>().multiply(who_T, output_errors);

        // hidden gradient
        Matrix<double> hidden_gradient = Matrix<double>().map(hidden, activation_function.second);
        hidden_gradient.multiply(hidden_errors);
        hidden_gradient.multiply(learning_rate);

        // input2hidden deltas
        auto intputs_T = Matrix<double>().transpose(inputs);
        auto weights_ih_deltas = Matrix<double>().multiply(hidden_gradient, intputs_T);

        weights_ih.add(weights_ih_deltas);
        bias_h.add(hidden_gradient);
    }

    NeuralNetwork copy()
    {
        return *this;
    }

    void mutate(const double &rate)
    {
        std::mt19937_64 rng;
        // initialize the random number generator with time-dependent seed
        uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::seed_seq ss{uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32)};
        rng.seed(ss);
        // initialize a uniform distribution between 0 and 1
        std::uniform_real_distribution<double> unif(0, 1);

        std::default_random_engine generator;
        std::normal_distribution<double> distribution(0, 1);
        std::function<double(double &)> mutate = [&](double &val) { return (unif(rng) < rate) ? (val + distribution(generator)) : val; };

        weights_ih.map(mutate);
        weights_ho.map(mutate);
        bias_h.map(mutate);
        bias_o.map(mutate);
    }
};
