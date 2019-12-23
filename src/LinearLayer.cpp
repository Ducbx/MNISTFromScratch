#include <vector>
#include <LinearLayer.hpp>
#include <iomanip>
#include <random>
#include <algorithm>

LinearLayer::LinearLayer(int node_count, int in_dim)
{
    this->in_dim = in_dim;
    this->out_dim = node_count;

    // Set up stuff to generate random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist{-1, 1};

    // Fill the weight vector
    this->weights.resize(node_count * in_dim);
    std::generate(begin(this->weights), end(this->weights), [&]() { return dist(gen); });
}

std::vector<float> LinearLayer::forward(std::vector<float>& input)
{
    if (input.size() != this->in_dim) {
        throw std::invalid_argument("Input size does not match number of neurons in LinearLayer");
    }

    std::vector<float> out(this->out_dim, 0.0f);

    // Perform matrix-vector multiplication
    for (int o = 0; o < this->out_dim; o++) {
        for (int i = 0; i < this->in_dim; i++) {
            out[o] += this->at(o, i) * input[i];
        }
    }

    return out;
}

float& LinearLayer::at(unsigned int row, unsigned int col)
{
    if ((row > this->out_dim) || (col > this->in_dim)) {
        throw std::out_of_range("Index out of range");
    }
    return this->weights[row * this->in_dim + col];
}



float& LinearLayer::operator()(unsigned int row, unsigned int col)
{
    return this->at(row, col);
}

std::ostream& operator<<(std::ostream& os, LinearLayer& obj)
{
    for (int r = 0; r < obj.out_dim; r++) {
        for (int c = 0; c < obj.in_dim; c++) {
            os << std::fixed << std::setprecision(4) << std::setw(7) << obj(r, c) << " ";
        }

        os << std::endl;
    }

    return os;
}