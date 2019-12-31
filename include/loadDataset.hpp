#ifndef loadDataset_HPP
#define loadDataset_HPP 

#include <string>
#include <vector>
#include <matrix.hpp>

std::vector<Matrix> load_labels(std::string path);
std::vector<Matrix> load_images(std::string path);

#endif