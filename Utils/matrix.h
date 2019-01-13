#pragma once

#include <fstream>
#include <vector>

class RowVector;
class ColumnVector;

class Matrix
{
public:
    Matrix() = default;
    Matrix(int n, int m);

    int Rows() const { return m_data.size(); }
    int Columns() const { return m_data[0].size(); }

    Matrix operator+(Matrix const& other) const;
    Matrix& operator+=(Matrix const& other);

    Matrix operator-(Matrix const& other) const;
    Matrix& operator-=(Matrix const& other);

    Matrix operator*(Matrix const& other) const;
    Matrix& operator*=(Matrix const& other);

    Matrix operator*(double other) const;
    Matrix& operator*=(double other);

    //Hadamard Product
    Matrix operator%(Matrix const& other) const;
    Matrix& operator%=(Matrix const& other);

    Matrix Transpose() const;
    Matrix Inverse() const;

    std::vector<double>& operator[](int row) { return m_data[row]; }
    std::vector<double> const& operator[](int row) const { return m_data[row]; }

private:
    std::vector<std::vector<double>> m_data;
};

std::ostream& operator <<(std::ostream& out, Matrix const& matrix);
std::istream& operator >>(std::istream& in, Matrix& matrix);