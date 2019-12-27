#ifndef loadDataset_HPP
#define loadDataset_HPP 

#include <string>
#include <vector>

std::vector<float> load_labels(std::string path);
std::vector<std::vector<float>> load_images(std::string path);

void print_dataset(std::vector<std::vector<float>>& images, std::vector<float>& labels);
void print_image(std::vector<float>& image);

#endif

