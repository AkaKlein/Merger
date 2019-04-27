#include "matrix.h"

#include <cassert>
#include <cmath>

#include "row_vector.h"
#include "column_vector.h"

using namespace std;

Matrix::Matrix(int n, int m)
    : m_data(n, vector<double>(m))
{
}


Matrix Matrix::operator+(Matrix const& other) const
{
    Matrix result(*this);
    result += other;
    return result;
}

Matrix& Matrix::operator+=(Matrix const& other)
{
    for (int i = 0; i < Rows(); ++i)
        for (int j = 0; j < Columns(); ++j)
            m_data[i][j] += other.m_data[i][j];

    return *this;
}

Matrix Matrix::operator-(Matrix const& other) const
{
    Matrix result(*this);
    result -= other;
    return result;
}

Matrix& Matrix::operator-=(Matrix const& other)
{
    for (int i = 0; i < Rows(); ++i)
        for (int j = 0; j < Columns(); ++j)
            m_data[i][j] -= other.m_data[i][j];

    return *this;
}

Matrix Matrix::operator*(Matrix const& other) const
{
    Matrix result(*this);
    result *= other;
    return result;
}

Matrix& Matrix::operator*=(Matrix const& other)
{
    Matrix result(Rows(), Columns());
    for (int i = 0; i < Rows(); ++i)
    {
        for (int j = 0; j < other.Columns(); ++j)
        {
            result[i][j] = 0;
            for (int k = 0; k < Columns(); ++k)
                result[i][j] += m_data[i][k] * other.m_data[k][j];
        }
    }

    m_data = result.m_data;
    return *this;
}

Matrix Matrix::operator*(double other) const
{
    Matrix result(*this);
    result *= other;
    return result;
}

Matrix& Matrix::operator*=(double other)
{
    for (int i = 0; i < Rows(); ++ i)
        for (int j = 0; j < Columns(); ++j)
            m_data[i][j] *= other;

    return *this;
}

Matrix Matrix::operator%(Matrix const& other) const
{
    Matrix result(*this);
    result %= other;
    return result;
}

Matrix& Matrix::operator%=(Matrix const& other)
{
    for (int i = 0; i < Rows(); ++i)
        for (int j = 0; j < Columns(); ++j)
            m_data[i][j] *= other.m_data[i][j];

    return *this;
}

Matrix Matrix::Transpose() const
{
    Matrix result(Columns(), Rows());
    for (int i = 0; i < Rows(); ++i)
        for (int j = 0; j < Columns(); ++j)
            result[j][i] = m_data[i][j];

    return result;
}

Matrix Matrix::Inverse() const
{
    assert(Rows() == Columns());
    int n = Rows();

    Matrix matrix(Rows(), 2 * Columns());
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            matrix[i][j] = m_data[i][j];
    for (int i = 0; i < n; ++i)
        for (int j = n; j < 2 * n; ++j)
            matrix[i][j] = (i == j - n) ? 1 : 0;

    for (int i = 0; i < n; ++i)
    {
        // Look for the best pivot.
        int pivot = i;
        for (int k = i + 1; k < n; ++k)
            if (std::fabs(matrix[pivot][i]) < std::fabs(matrix[k][i]))
                pivot = k;

        // No pivot different of zero, so the matrix has no inverse.
        if (std::fabs(matrix[pivot][i]) < 1e-5)
            throw std::runtime_error("Matrix::Inverse: The matrix is not invertible");
        
        // Swap the pivot row.
        std::swap(matrix[i], matrix[pivot]);

        // Divide the row by the pivot.
        double pivot_value = matrix[i][i];
        for (int k = 0; k < 2 * n; ++k)
            matrix[i][k] /= pivot_value;

        for (int k = 0; k < n; ++k)
        {
            if (k != i)
            {
                double coefficient = matrix[k][i];
                for (int h = 0; h < 2 * n; ++h)
                    matrix[k][h] -= matrix[i][h] * coefficient; 
            }
        }
    }

    Matrix result(Rows(), Columns());
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            result[i][j] = matrix[i][j + n];
    return result;
}

ostream& operator <<(ostream& out, Matrix const& matrix)
{
    int n = matrix.Rows();
    int m = matrix.Columns();

    out << n << ' ' << m << endl;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            out << matrix[i][j];
            if (j != m - 1)
                out << ' ';
        }
        out << endl;
    }

    return out;
}

istream& operator >>(istream& in, Matrix& matrix)
{
    int n, m;
    in >> n >> m;

    matrix = Matrix(n, m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            in >> matrix[i][j];

    return in;
}
