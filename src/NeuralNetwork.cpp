#include <vector>
#include <NeuralNetwork.hpp>

NeuralNetwork::NeuralNetwork(const std::vector<int> hl_node_counts)
{
    this->in_w = 28;
    this->in_h = 28;
    this->o_size = 10;

    int in_dim = this->in_w * this->in_h;
    for (int node_count : hl_node_counts) {
        this->layers.push_back(Matrix(node_count, in_dim));
        in_dim = node_count;
    }

    this->layers.push_back(Matrix(this->o_size, in_dim));

    // Initialize with random weights
    for (Matrix& mat : this->layers) {
        mat.random_fill(-1.0f, 1.0f);
    }
}

Matrix NeuralNetwork::forward(Matrix input)
{
    for (Matrix& layer : this->layers) {
        input = Matrix::matmul(layer, input);
        input = Matrix::sigmoid(input);
    }

    return input;
}

std::ostream& operator<<(std::ostream& os, NeuralNetwork& obj)
{
    os << "Input width:  " << obj.in_w << std::endl;
    os << "Input height: " << obj.in_h << std::endl;
    os << "Output dim:   " << obj.o_size << std::endl << std::endl;

    for (int i = 0; i < obj.layers.size(); i++) {
        os << "  Layer " << i << ": neurons " << obj.layers[i].n_rows 
           << "   in dim " << obj.layers[i].n_cols << std::endl;
    }

    return os;
}