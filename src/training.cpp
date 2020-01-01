#include <training.hpp>
#include <NeuralNetwork.hpp>
#include <matrix.hpp>
#include <iomanip>
#include <random>
#include <numeric>
#include <algorithm>

std::vector<Matrix> backprop(const NeuralNetwork& net, const Matrix& image, const Matrix& label);
void gradient_descent(NeuralNetwork& net, std::vector<std::vector<Matrix>>& delta_weights, float learning_rate);
std::vector<std::vector<int>> get_minibatch_indices(int n_examples, int batch_size);
void print_evaluation(const Matrix& image, const Matrix& label, const Matrix& out);


void train_iteration(NeuralNetwork& net, const std::vector<Matrix>& images, const std::vector<Matrix>& labels, int batch_size, float learning_rate)
{
    std::vector<std::vector<int>> minibatch_indices = get_minibatch_indices(images.size(), batch_size);

    for (std::vector<int>& batch : minibatch_indices) {
        std::vector<std::vector<Matrix>> delta_weights(batch.size());

        // Calculate dC/dw over batch in parallel
        #pragma omp parallel for schedule(guided)
        for (int i = 0; i < batch.size(); i++) {
            int index = batch[i];
            delta_weights[i] = backprop(net, images[index], labels[index]);
        }

        // Apply gradient
        gradient_descent(net, delta_weights, learning_rate);
    }
}


std::vector<Matrix> backprop(const NeuralNetwork& net, const Matrix& image, const Matrix& label)
{
    std::vector<Matrix> activations = net.forwardGrad(image);
    std::vector<Matrix> delta_errs, dC_dw;
    Matrix dC_da, da_dz;

    // Calculate deltas at each node
    for (int i = net.layers.size() - 1; i >= 0; i--) {
        da_dz = Matrix::schur( // Calculation is the same at every layer
            activations[i],
            Matrix::sub(Matrix(activations[i].n_rows, activations[i].n_cols, 1.0f), activations[i])
        );

        if (i == (net.layers.size() - 1)) { //Output layer
            dC_da = Matrix::sub(label, activations[i]);
        } else { // Internal layers
            dC_da = Matrix::matmul(Matrix::transpose(net.layers[i + 1]), delta_errs.front());
        }

        delta_errs.insert(delta_errs.begin(), Matrix::schur(dC_da, da_dz));
    }

    activations.insert(activations.begin(), image);
    for (int i = 0; i < net.layers.size(); i++) {
        dC_dw.push_back(
            Matrix::matmul(delta_errs[i], Matrix::transpose(activations[i]))
        );
    }

    return dC_dw;
}

void gradient_descent(NeuralNetwork& net, std::vector<std::vector<Matrix>>& delta_weights, float learning_rate)
{
    std::vector<Matrix> avg_deltas;
    for (const Matrix& mat : net.layers) {
        avg_deltas.push_back(Matrix(mat.n_rows, mat.n_cols));
    }

    // Sum up delta weights
    for (const std::vector<Matrix>& delta : delta_weights) {
        for (int i = 0; i < delta.size(); i++) {
            avg_deltas[i] = Matrix::add(avg_deltas[i], delta[i]);
        }
    }

    // Apply gradients
    for (int i = 0; i < net.layers.size(); i++) {
        net.layers[i] = Matrix::add(net.layers[i], Matrix::divide(avg_deltas[i], delta_weights.size() * (1.0f / learning_rate)));
    }
}

float evaluate_network(const NeuralNetwork& net, const std::vector<Matrix>& images, const std::vector<Matrix>& labels, bool print)
{
    int correct = 0;
    
    // Reduce over correct
    #pragma omp parallel for reduction(+ : correct)
    for (int index = 0; index < images.size(); index++) {
        const Matrix out = net.forward(images[index]);

        if (Matrix::argmax(out) == Matrix::argmax(labels[index])) {
            correct++;
        }
    }

    if (print) {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist{0, (int)images.size()};
        int index = dist(gen);
        print_evaluation(images[index], labels[index], net.forward(images[index]));
    }


    return (float)correct / (float)images.size();
}

std::vector<std::vector<int>> get_minibatch_indices(int n_examples, int batch_size)
{
    std::vector<int> indices(n_examples);
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), std::mt19937{std::random_device{}()});

    std::vector<std::vector<int>> minibatches;
    std::vector<int> batch;
    for (int i = 0; i < indices.size(); i++) {
        if ((i + 1) % batch_size == 0) {
            minibatches.push_back(batch);
            batch.clear();
        }
        batch.push_back(i);
    }

    return minibatches;
}

void print_evaluation(const Matrix& image, const Matrix& label, const Matrix& out)
{
    for (int r = 0; r < 28; r++) {
        for (int c = 0; c < 28; c++) {
            if (image(r * 28 + c) > 0) {
                std::cout << "# ";
            } else {
                std::cout << ". ";
            }
        }

        if (r == 8) {
            std::cout << "\t      Out     Label";
        } else if ( (r > 9) && (r < 20)) {
            std::cout << "\t" << r - 10 << ":   " << std::fixed << std::setprecision(2) << out(r-10);
            std::cout << "\t" << (int)label(r-10);
        }

        std::cout << std::endl;
    }
}