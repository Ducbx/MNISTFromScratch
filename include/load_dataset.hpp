#ifndef LOAD_DATASET_HPP
#define LOAD_DATASET_HPP 

#include <string>
#include <vector>

std::vector<uint8_t> load_labels(std::string path);
std::vector<std::vector<uint8_t>> load_images(std::string path);
void print_dataset(std::vector<uint8_t>& labels, std::vector<std::vector<uint8_t>>& images);
void print_image(std::vector<uint8_t>& image);

#endif

