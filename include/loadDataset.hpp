#ifndef loadDataset_HPP
#define loadDataset_HPP 

#include <string>
#include <vector>
#include <matrix.hpp>

std::vector<Matrix> load_labels(std::string path);
std::vector<Matrix> load_images(std::string path);

void print_dataset(const std::vector<Matrix>& images, const std::vector<Matrix>& labels);
void print_image(const Matrix& image, const Matrix& label);

#endif