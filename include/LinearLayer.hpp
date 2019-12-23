#ifndef LINEAR_LAYER_HPP
#define LINEAR_LAYER_HPP

#include <vector>
#include <iostream>

class LinearLayer
{
public:
    int in_dim;
    int out_dim;
    
    std::vector<float> weights;

    LinearLayer(int node_count, int in_dim);

    std::vector<float> forward(std::vector<float>& input);
    float& at(unsigned int row, unsigned int col);

    // Overloads
    float& operator()(unsigned int row, unsigned int col);
    friend std::ostream& operator<<(std::ostream& os, LinearLayer& dt);
};

#endif