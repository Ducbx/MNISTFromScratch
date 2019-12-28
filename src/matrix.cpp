#include <matrix.hpp>
#include <vector>
#include <iomanip>
#include <math.h>
#include <random>
#include <algorithm>

////////////////////////////////////////
// Constructors
////////////////////////////////////////
Matrix::Matrix(unsigned int n_rows, unsigned int n_cols)
{
    this->n_rows = n_rows;
    this->n_cols = n_cols;

    this->data.resize(n_rows * n_cols, 0.0f);
}

Matrix::Matrix()
{
    this->n_rows = 0;
    this->n_cols = 0;
}

void Matrix::resize(unsigned int n_rows, unsigned int n_cols)
{
    this->n_rows = n_rows;
    this->n_cols = n_cols;

    this->data.clear();
    this->data.resize(this->n_rows * this->n_cols, 0.0f);
}

void Matrix::random_fill(float low, float high)
{
    // Set up stuff to generate random numbers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist{low, high};

    std::generate(begin(this->data), end(this->data), [&]() { return dist(gen); });
}

////////////////////////////////////////
// Matrix operations
////////////////////////////////////////
Matrix Matrix::matmul(Matrix a, Matrix b)
{
    // Check dimensions
    if (a.n_cols != b.n_rows) {
        throw std::invalid_argument("Inner dimensions do not match!");
    }

    Matrix out = Matrix(a.n_rows, b.n_cols);

    for (int r = 0; r < a.n_rows; r++) {
        for (int c = 0; c < b.n_cols; c++) {
            float sum = 0.0f;

            for (int j = 0; j < b.n_rows; j++) {
                sum += a(r, j) * b(j, c);
            }

            out(r, c) = sum;
        }
    }

    return out;
}

Matrix Matrix::add(Matrix a, Matrix b)
{
    // Check dimensions
    if ( (a.n_rows != b.n_rows) || (a.n_cols != b.n_cols) ) {
        throw std::invalid_argument("Dimensions do not match!");
    }

    Matrix out = Matrix(a.n_rows, a.n_cols);
    std::transform(a.data.begin(), a.data.end(), b.data.begin(), out.data.begin(), std::plus<float>());

    return out;
}

Matrix Matrix::sub(Matrix a, Matrix b)
{
    // Check dimensions
    if ( (a.n_rows != b.n_rows) || (a.n_cols != b.n_cols) ) {
        throw std::invalid_argument("Dimensions do not match!");
    }

    Matrix out = Matrix(a.n_rows, a.n_cols);
    std::transform(a.data.begin(), a.data.end(), b.data.begin(), out.data.begin(), std::minus<float>());

    return out;
}

Matrix Matrix::divide(Matrix a, float b)
{
    Matrix out = Matrix(a.n_rows, a.n_cols);
    std::transform(a.data.begin(), a.data.end(), out.data.begin(), [&b](float& c) { return c / b; } );

    return out;
}

Matrix Matrix::sigmoid(Matrix a)
{
    Matrix out = Matrix(a.n_rows, a.n_cols);

    for (int r = 0; r < a.n_rows; r++) {
        for (int c = 0; c < a.n_cols; c++) {
            out(r, c) = 1.0f / (1.0f + expf(-1.0f * a(r, c)));
        }
    }

    return out;
}

int Matrix::argmax()
{
    return std::distance(this->data.begin(), std::max_element(this->data.begin(), this->data.end()));
}

////////////////////////////////////////
// Misc
////////////////////////////////////////
float& Matrix::operator()(unsigned int row, unsigned int col)
{
    if ((row >= this->n_rows) || (col >= this->n_cols)) {
        throw std::out_of_range("Index out of range");
    }

    return this->data[row * this->n_cols + col];
}

float& Matrix::operator()(unsigned int index)
{
    if (index >= (this->n_rows * this->n_cols)) {
        throw std::out_of_range("Index out of range");
    }

    return this->data[index];
}

float Matrix::operator()(unsigned int row, unsigned int col) const
{
    if ((row >= this->n_rows) || (col >= this->n_cols)) {
        throw std::out_of_range("Index out of range");
    }

    return this->data[row * this->n_cols + col];
}

float Matrix::operator()(unsigned int index) const
{
    if (index >= (this->n_rows * this->n_cols)) {
        throw std::out_of_range("Index out of range");
    }

    return this->data[index];
}

std::ostream& operator<<(std::ostream& os, Matrix& obj)
{
    for (int r = 0; r < obj.n_rows; r++) {
        for (int c = 0; c < obj.n_cols; c++) {
            os << std::fixed << std::setprecision(4) << std::setw(7) << obj(r, c) << " ";
        }

        os << std::endl;
    }

    return os;
}