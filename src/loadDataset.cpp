#include <iostream>
#include <fstream>
#include <iomanip>
#include <loadDataset.hpp>
#include <vector>
#include <algorithm> 

unsigned int reverse_endianness(unsigned int num);

std::vector<Matrix> load_labels(std::string path)
{
    std::ifstream file;
    std::vector<uint8_t> buf;
    std::vector<Matrix> labels;

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
        file.close();
        return labels;
    }


    buf.resize(num_labels);
    file.read((char *)&buf[0], sizeof(buf[0]) * num_labels);

    for (int i = 0; i < num_labels; i++) {
        Matrix tmp = Matrix(10, 1);
        tmp(buf[i]) = 1.0f;

        labels.push_back(tmp);
    }

    return labels;
}

std::vector<Matrix> load_images(std::string path)
{
    std::ifstream file;
    std::vector<Matrix> images;
    std::vector<uint8_t> buf;

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
        file.close();
        return images;
    }

    if ((num_rows != 28) || (num_cols != 28)) {
        std::cerr << "Expected row, col: (28, 20)" << "\trow, col read: " "(" << num_rows << ", " << num_cols << ")" << std::endl;
        file.close();
        return images;
    }

    buf.resize(num_rows * num_cols);
    for (int i = 0; i < num_images; i++) {
        file.read((char *)&buf[0], sizeof(buf[0]) * num_rows * num_cols);
        
        Matrix tmp = Matrix(num_rows * num_cols, 1);
        tmp.data.assign(buf.begin(), buf.end());

        images.push_back(Matrix::divide(tmp, 255.0f));
    }

    return images;
}

void print_dataset(const std::vector<Matrix>& images, const std::vector<Matrix>& labels)
{   
    for (int i = 0; i < images.size(); i++) {
        print_image(images[i], labels[i]);
        std::cout << std::endl;
    }
}

void print_image(const Matrix& image, const Matrix& label)
{
    for (int r = 0; r < 28; r++) {
        for (int c = 0; c < 28; c++) {
            if (image(r * 28 + c) > 0) {
                std::cout << "# ";
            } else {
                std::cout << ". ";
            }
        }

        if ( (r > 7) && (r < 18)) {
            std::cout << "   " << r - 8 << ": " << label(r - 8);
        }

        std::cout << std::endl;
    }
}

unsigned int reverse_endianness(unsigned int num)
{
    return ((num & 0xFF000000) >> 24) | 
           ((num & 0x00FF0000) >> 8)  | 
           ((num & 0x0000FF00) << 8)  | 
           ((num & 0x000000FF) << 24);
}