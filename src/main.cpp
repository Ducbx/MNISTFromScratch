#include <vector>
#include <loadDataset.hpp>
#include <iostream>
#include <NeuralNetwork.hpp>

int main(int argc, char const *argv[])
{
    std::vector<Matrix> train_labels = load_labels("../dataset/train-labels-idx1-ubyte");
    std::vector<Matrix> test_labels = load_labels("../dataset/t10k-labels-idx1-ubyte");

    std::vector<Matrix> test_images = load_images("../dataset/t10k-images-idx3-ubyte");
    std::vector<Matrix> train_images = load_images("../dataset/train-images-idx3-ubyte");

    NeuralNetwork net = NeuralNetwork({16, 16});

    std::cout << net << std::endl;

    auto out = net.forward(train_images[0]);
    std::cout << out << std::endl;
    // evaluate_network(net, train_images, train_labels);
    
    return 0;
}