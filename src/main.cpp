#include <vector>
#include <loadDataset.hpp>
#include <iostream>
#include <NeuralNetwork.hpp>
#include <training.hpp>

int main()
{
    std::vector<Matrix> train_labels = load_labels("../dataset/train-labels-idx1-ubyte");
    std::vector<Matrix> test_labels = load_labels("../dataset/t10k-labels-idx1-ubyte");

    std::vector<Matrix> test_images = load_images("../dataset/t10k-images-idx3-ubyte");
    std::vector<Matrix> train_images = load_images("../dataset/train-images-idx3-ubyte");

    NeuralNetwork net = NeuralNetwork({16, 16});

    std::cout << net << std::endl;

    std::cout << "Initial performance: " << evaluate_network(net, test_images, test_labels, false) * 100 << "%" << std::endl;
    for (int i = 0; i < 10000; i++) {
        std::cout << "###################################################" << std::endl;
        std::cout << "Epoch " << i + 1 << std::endl;

        train_iteration(net, train_images, train_labels, 0.2f);

        float accuracy = evaluate_network(net, test_images, test_labels, true);
        std::cout << "Test set accuracy: " << accuracy * 100 << "%" << std::endl;
    }

    return 0;
}