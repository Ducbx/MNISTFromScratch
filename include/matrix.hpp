#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <vector>
#include <iostream>

class Matrix
{
public:
    int n_rows;
    int n_cols;
    std::vector<float> data;

    Matrix(unsigned int n_rows, unsigned int n_cols);
    Matrix();

    void resize(unsigned int n_rows, unsigned int n_cols);
    void random_fill(float low, float high);
    int argmax();

    static Matrix matmul(Matrix a, Matrix b);
    static Matrix add(Matrix a, Matrix b);
    static Matrix sub(Matrix a, Matrix b);
    static Matrix divide(Matrix a, float b);
    static Matrix sigmoid(Matrix a);

    float& operator()(unsigned int row, unsigned int col);
    float& operator()(unsigned int index);
    float operator()(unsigned int row, unsigned int col) const;
    float operator()(unsigned int index) const;
};

std::ostream& operator<<(std::ostream& os, Matrix& obj);

#endif