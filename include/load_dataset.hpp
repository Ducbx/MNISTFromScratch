#ifndef LOAD_DATASET_HPP
#define LOAD_DATASET_HPP 

#include <string>
#include <vector>

std::vector<uint8_t> load_labels(std::string path);
std::vector<std::vector<uint8_t>> load_images(std::string path);

unsigned int reverse_endianness(unsigned int num);

#endif

