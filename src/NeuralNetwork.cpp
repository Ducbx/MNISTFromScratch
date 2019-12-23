#include <vector>
#include <NeuralNetwork.hpp>
#include <LinearLayer.hpp>
#include <math.h>

// XXX Need to optimize these functions to do ops in place or in a buffer
// XXX I guess I should measure vector allocation overhead first
// XXX Also, try and change code so g++ will auto vectorize it (in the mat-vec mul)

std::vector<float> sigmoid(std::vector<float> input);

NeuralNetwork::NeuralNetwork(int input_width, int input_height, int output_size, const std::vector<int> hl_node_counts)
{
    this->in_w = input_width;
    this->in_h = input_height;
    this->o_size = output_size;

    int in_dim = input_width * input_height;
    for (int node_count : hl_node_counts) {
        LinearLayer tmp = LinearLayer(node_count, in_dim);
        this->layers.push_back(tmp);
        in_dim = tmp.out_dim;
    }

    this->layers.push_back(LinearLayer(output_size, in_dim));
}

std::vector<float> NeuralNetwork::forward(std::vector<float> input)
{
    for (LinearLayer& layer : this->layers) {
        input = layer.forward(input);
        input = sigmoid(input);
    }

    return input;
}

std::vector<float> sigmoid(std::vector<float> input)
{
    std::vector<float> out(input.size());

    for (int i = 0; i < input.size(); i++) {
        out[i] = 1 / (1 + expf(-1 * input[i]));
    }

    return out;
}

std::ostream& operator<<(std::ostream& os, NeuralNetwork& obj)
{
    os << "Input width:  " << obj.in_w << std::endl;
    os << "Input height: " << obj.in_h << std::endl;
    os << "Output dim:   " << obj.o_size << std::endl << std::endl;

    for (int i = 0; i < obj.layers.size(); i++) {
        os << "  Layer " << i << ": neurons " << obj.layers[i].out_dim 
           << "   in dim " << obj.layers[i].in_dim << std::endl;
    }

    return os;
}