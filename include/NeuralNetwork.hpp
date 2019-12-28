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

    Matrix forward(Matrix input);

    // Overloads
    friend std::ostream& operator<<(std::ostream& os, NeuralNetwork& dt);
};

#endif