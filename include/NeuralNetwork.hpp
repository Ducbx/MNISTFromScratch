#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include <matrix.hpp>

class NeuralNetwork
{
public:
    int in_w;
    int in_h;
    int o_size;
    std::vector<Matrix> layers;

    NeuralNetwork(const std::vector<int> hl_node_counts);

    Matrix forward(const Matrix& input) const;
    std::vector<Matrix> forwardGrad(const Matrix& input) const;

    // Overloads
    friend std::ostream& operator<<(std::ostream& os, NeuralNetwork& dt);
};

#endif