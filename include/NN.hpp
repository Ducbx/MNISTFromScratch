#ifndef NN_HPP
#define NN_HPP

#include <vector>
#include <LinearLayer.hpp>

class NN
{
public:
    int in_w;
    int in_h;
    int o_size;
    std::vector<int> layer_sizes;

    std::vector<std::vector<float>> weights;

    NN(int input_width, int input_height, int outputz_size, std::vector<int> hl_node_counts);
};

#endif