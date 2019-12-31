#ifndef TRAINING_HPP
#define TRAINING_HPP

#include <matrix.hpp>
#include <NeuralNetwork.hpp>


void train_iteration(NeuralNetwork& net, const std::vector<Matrix>& images, const std::vector<Matrix>& labels, float learning_rate);
float evaluate_network(const NeuralNetwork& net, const std::vector<Matrix>& images, const std::vector<Matrix>& labels, bool print);

#endif