#include <vector>
#include <loadDataset.hpp>
#include <iostream>
#include <NeuralNetwork.hpp>

int main(int argc, char const *argv[])
{
    std::vector<uint8_t> train_labels = load_labels("../dataset/train-labels-idx1-ubyte");
    std::vector<uint8_t> test_labels = load_labels("../dataset/t10k-labels-idx1-ubyte");

    std::vector<std::vector<uint8_t>> test_images = load_images("../dataset/t10k-images-idx3-ubyte");
    std::vector<std::vector<uint8_t>> train_images = load_images("../dataset/train-images-idx3-ubyte");

    NeuralNetwork net = NeuralNetwork(3, 3, 4, {8, 7, 6, 5});

    std::cout << net << std::endl;

    std::vector<float> input{0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8};

    auto out = net.forward(input);

    for (float o : out) {
        std::cout << o << std::endl;
    }

    return 0;
}