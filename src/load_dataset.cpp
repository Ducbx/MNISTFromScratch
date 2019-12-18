#include <iostream>
#include <fstream>
#include <iomanip>
#include <load_dataset.hpp>
#include <vector>

unsigned int reverse_endianness(unsigned int num);

std::vector<uint8_t> load_labels(std::string path)
{
    std::ifstream file;
    std::vector<uint8_t> labels;
    unsigned int magic_number;
    unsigned int num_labels;

    file.open(path, std::ios::binary | std::ios::in);
    
    if (file.is_open() == false) {
        std::cerr << "Error opening file, is the path correct?" << std::endl;
        return labels;
    }

    file.read((char *) &magic_number, sizeof(magic_number));
    file.read((char *) &num_labels,   sizeof(num_labels));

    magic_number = reverse_endianness(magic_number);
    num_labels   = reverse_endianness(num_labels);

    if (magic_number != 0x00000801) {
        std::cerr << "Expected magic number: " << 0x00000801 << "\tMagic number read: " << magic_number << std::endl;
        return labels;
    }


    labels.resize(num_labels);
    for (int i = 0; i < num_labels; i++) {
        file.read((char *)&labels[i], sizeof(labels[i]));
        
        // Sanity check
        if (labels[i] > 9) {
            std::cerr << "Unexpected label: " << labels[i] << std::endl;
            labels.resize(0);
            return labels;
        }
    }

    return labels;
}

std::vector<std::vector<uint8_t>> load_images(std::string path)
{
    std::ifstream file;
    std::vector<std::vector<uint8_t>> images;
    unsigned int magic_number;
    unsigned int num_images;
    unsigned int num_rows;
    unsigned int num_cols;

    file.open(path, std::ios::binary | std::ios::in);
    
    if (file.is_open() == false) {
        std::cerr << "Error opening file, is the path correct?" << std::endl;
        return images;
    }

    file.read((char *) &magic_number, sizeof(magic_number));
    file.read((char *) &num_images,   sizeof(num_images));
    file.read((char *) &num_rows,     sizeof(num_rows));
    file.read((char *) &num_cols,     sizeof(num_cols));

    magic_number = reverse_endianness(magic_number);
    num_images   = reverse_endianness(num_images);
    num_rows     = reverse_endianness(num_rows);
    num_cols     = reverse_endianness(num_cols);

    if (magic_number != 0x00000803) {
        std::cerr << "Expected magic number: " << 0x00000803 << "\tMagic number read: " << magic_number << std::endl;
        return images;
    }

    if ((num_rows != 28) || (num_cols != 28)) {
        std::cerr << "Expected row, col: (28, 20)" << "\trow, col read: " "(" << num_rows << ", " << num_cols << ")" << std::endl;
        return images;
    }

    for (int i = 0; i < num_images; i++) {
        std::vector<uint8_t> tmp(num_rows * num_cols);
        uint8_t pixel;

        for (int p = 0; p < (num_rows * num_cols); p++) {
            file.read((char *)&tmp[p], sizeof(tmp[p]));
        }

        images.push_back(tmp);
    }

    return images;
}

unsigned int reverse_endianness(unsigned int num)
{
    return ((num & 0xFF000000) >> 24) | 
           ((num & 0x00FF0000) >> 8)  | 
           ((num & 0x0000FF00) << 8)  | 
           ((num & 0x000000FF) << 24);
}

void print_dataset(std::vector<uint8_t>& labels, std::vector<std::vector<uint8_t>>& images)
{
    for (int i = 0; i < images.size(); i++) {
        std::cout << (int) labels[i] << std::endl;
        print_image(images[i]);
    }
}

void print_image(std::vector<uint8_t>& image)
{
    for (int r = 0; r < 28; r++) {
        for (int c = 0; c < 28; c++) {
            if (image[r * 28 + c] > 0) {
                std::cout << "# ";
            } else {
                std::cout << ". ";
            }
        }

        std::cout << std::endl;
    }
}