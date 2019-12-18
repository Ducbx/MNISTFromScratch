#include <vector>
#include <load_dataset.hpp>
#include <iostream>

int main(int argc, char const *argv[])
{
    std::vector<uint8_t> train_labels = load_labels("../dataset/train-labels-idx1-ubyte");
    std::vector<uint8_t> test_labels = load_labels("../dataset/t10k-labels-idx1-ubyte");

    std::vector<std::vector<uint8_t>> test_images = load_images("../dataset/t10k-images-idx3-ubyte");
    std::vector<std::vector<uint8_t>> train_images = load_images("../dataset/train-images-idx3-ubyte");

    print_dataset(train_labels, train_images);
    print_dataset(test_labels, test_images);

    return 0;
}