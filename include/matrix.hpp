#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

class Matrix
{
public:
    unsigned int n_rows;
    unsigned int n_cols;
    std::vector<float> data;

    Matrix(unsigned int n_rows, unsigned int n_cols);
    Matrix(unsigned int n_rows, unsigned int n_cols, float fill);
    Matrix();

    void random_fill(float low, float high);

    static int argmax(const Matrix& a);
    static Matrix transpose(const Matrix& a);
    static Matrix matmul(const Matrix& a, const Matrix& b);
    static Matrix schur(const Matrix& a, const Matrix& b);
    static Matrix add(const Matrix& a, const Matrix& b);
    static Matrix sub(const Matrix& a, const Matrix& b);
    static Matrix divide(const Matrix& a, float b);
    static Matrix mult(const Matrix& a, float b);

    
    static Matrix sigmoid(const Matrix& a);

    float& operator()(unsigned int row, unsigned int col);
    float& operator()(unsigned int index);
    float operator()(unsigned int row, unsigned int col) const;
    float operator()(unsigned int index) const;
};

#endif