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

Matrix::Matrix(unsigned int n_rows, unsigned int n_cols, float fill)
{
    this->n_rows = n_rows;
    this->n_cols = n_cols;

    this->data.resize(n_rows * n_cols, fill);
}

Matrix::Matrix()
{
    this->n_rows = 0;
    this->n_cols = 0;
}


void Matrix::random_fill(float low, float high)
{
    // Set up stuff to generate random numbers
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<float> dist{low, high};

    std::generate(begin(this->data), end(this->data), [&]() { return dist(gen); });
}


////////////////////////////////////////
// Matrix operations
////////////////////////////////////////
Matrix Matrix::transpose(const Matrix& a)
{
    Matrix out = Matrix(a.n_cols, a.n_rows);

    for (int r = 0; r < a.n_rows; r++) {
        for (int c = 0; c < a.n_cols; c++) {
            out.data[c * out.n_cols + r] = a.data[r * a.n_cols + c];
        }
    }

    return out;
}

Matrix Matrix::matmul(const Matrix& a, const Matrix& b)
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
                sum += a.data[r * a.n_cols + j] * b.data[j * b.n_cols + c];
            }

            out.data[r * out.n_cols + c] = sum;
        }
    }

    return out;
}

Matrix Matrix::add(const Matrix& a, const Matrix& b)
{
    // Check dimensions
    if ( (a.n_rows != b.n_rows) || (a.n_cols != b.n_cols) ) {
        throw std::invalid_argument("Dimensions do not match!");
    }

    Matrix out = Matrix(a.n_rows, a.n_cols);
    std::transform(a.data.begin(), a.data.end(), b.data.begin(), out.data.begin(), std::plus<float>());

    return out;
}

Matrix Matrix::sub(const Matrix& a, const Matrix& b)
{
    // Check dimensions
    if ( (a.n_rows != b.n_rows) || (a.n_cols != b.n_cols) ) {
        throw std::invalid_argument("Dimensions do not match!");
    }

    Matrix out = Matrix(a.n_rows, a.n_cols);
    std::transform(a.data.begin(), a.data.end(), b.data.begin(), out.data.begin(), std::minus<float>());

    return out;
}

Matrix Matrix::schur(const Matrix& a, const Matrix& b)
{
    if ( (a.n_rows != b.n_rows) || (a.n_cols != b.n_cols) ) {
        throw std::invalid_argument("Dimensions do not match!");
    }

    Matrix out = Matrix(a.n_rows, a.n_cols);
    std::transform(a.data.begin(), a.data.end(), b.data.begin(), out.data.begin(), std::multiplies<float>());

    return out;
}

Matrix Matrix::divide(const Matrix& a, float b)
{
    Matrix out = Matrix(a.n_rows, a.n_cols);
    std::transform(a.data.begin(), a.data.end(), out.data.begin(), [&b](const float& c) { return c / b; } );

    return out;
}

Matrix Matrix::mult(const Matrix& a, float b)
{
    Matrix out = Matrix(a.n_rows, a.n_cols);
    std::transform(a.data.begin(), a.data.end(), out.data.begin(), [&b](const float& c) { return c * b; } );

    return out;
}

Matrix Matrix::sigmoid(const Matrix& a)
{
    Matrix out = Matrix(a.n_rows, a.n_cols);

    std::transform(a.data.begin(), a.data.end(), out.data.begin(), [](const float& c) { return 1.0f / (1.0f + expf(-1.0f * c)); } );

    return out;
}

int Matrix::argmax(const Matrix& a)
{
    return std::distance(a.data.begin(), std::max_element(a.data.begin(), a.data.end()));
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