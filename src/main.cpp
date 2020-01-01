#include <vector>
#include <loadDataset.hpp>
#include <iostream>
#include <NeuralNetwork.hpp>
#include <training.hpp>

int main()
{
    int epochs = 1000;
    int batch_size = 1024;
    float learning_rate = 1.0f;

    std::vector<Matrix> train_images = load_images("../dataset/train-images-idx3-ubyte");
    std::vector<Matrix> train_labels = load_labels("../dataset/train-labels-idx1-ubyte");

    std::vector<Matrix> test_images  = load_images("../dataset/t10k-images-idx3-ubyte");
    std::vector<Matrix> test_labels  = load_labels("../dataset/t10k-labels-idx1-ubyte");

    NeuralNetwork net = NeuralNetwork({16, 16});

    std::cout << "Initial performance: " << evaluate_network(net, test_images, test_labels, false) * 100 << "%" << std::endl;
    for (int i = 0; i < epochs; i++) {
        std::cout << "###################################################" << std::endl;
        std::cout << "Epoch " << i + 1 << std::endl;

        train_iteration(net, train_images, train_labels, batch_size, learning_rate);

        float accuracy = evaluate_network(net, test_images, test_labels, true);
        std::cout << "Test set accuracy: " << accuracy * 100 << "%" << std::endl;

        // Clip small weights every 100 epochs to ??? help with the gradient descent ???
        if ((i + 1) % 100 == 0) {
            net.clip_weights(0.01);
            accuracy = evaluate_network(net, test_images, test_labels, false);
            std::cout << "Test set accuracy after clipping: " << accuracy * 100 << "%" << std::endl;
        }
    }

    return 0;
}