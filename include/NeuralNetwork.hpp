#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include <vector>
#include <LinearLayer.hpp>

class NeuralNetwork
{
public:
    int in_w;
    int in_h;
    int o_size;
    std::vector<LinearLayer> layers;

    NeuralNetwork(int input_width, int input_height, int output_size, const std::vector<int> hl_node_counts);

    std::vector<float> forward(std::vector<float> input);

    // Overloads
    friend std::ostream& operator<<(std::ostream& os, NeuralNetwork& dt);
};

#endif