#include <vector>
#include <NN.hpp>

/////////////////////////////////////////////////////////////////////////
//
//          NN class definition
//
/////////////////////////////////////////////////////////////////////////
NN::NN(int input_width, int input_height, int output_size, std::vector<int> hl_node_counts)
{
    this->in_w = input_width;
    this->in_h = input_height;
    this->o_size = output_size;

    std::vector<int> layer_sizes;
}
