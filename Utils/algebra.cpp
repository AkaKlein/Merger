#include "algebra.h"

#include <cmath>

ColumnVector operator*(Matrix const& matrix, ColumnVector const& v)
{
    ColumnVector result(matrix.Rows());
    for (int i = 0; i < matrix.Rows(); ++i)
    {
        result[i] = 0;
        for (int j = 0; j < matrix.Columns(); ++j)
            result[i] += matrix[i][j] * v[j];
    }

    return result;
}

Matrix operator*(ColumnVector const& c, RowVector const& r)
{
    Matrix result(c.Size(), r.Size());
    for (int i = 0; i < c.Size(); ++i)
    {
        for (int j = 0; j < r.Size(); ++j)
            result[i][j] = c[i] * r[j];
    }
    
    return result;
}

ColumnVector Transpose(RowVector const& v)
{
    ColumnVector result(v.Size());
    for (int i = 0; i < v.Size(); ++i)
        result[i] = v[i];

    return result;
}

RowVector Transpose(ColumnVector const& v)
{
    RowVector result(v.Size());
    for (int i = 0; i < v.Size(); ++i)
        result[i] = v[i];
    
    return result;
}

Matrix operator*(double k, Matrix const& matrix) { return matrix * k; }

ColumnVector operator*(double k, ColumnVector const& v) { return v * k; }

RowVector operator*(double k, RowVector const& v) { return v * k; }

ColumnVector Diagonal(Matrix const& matrix)
{
    ColumnVector diagonal(matrix.Rows());
    for (int i = 0; i < matrix.Rows(); ++i)
        diagonal[i] = matrix[i][i];
    return diagonal;
}

Matrix operator%(ColumnVector const& v, Matrix const& m)
{
    Matrix result = m;
    for (int i = 0; i < m.Rows(); ++i)
        for (int j = 0; j < m.Columns(); ++j)
            result[i][j] *= v[i];
    return result;
}

Matrix operator%(Matrix const& m, ColumnVector const& v) { return v % m; }

double norm(ColumnVector const& v)
{
    double result = 0;
    for (int i = 0; i < v.Size(); ++i)
        result += v[i] * v[i];
    return std::sqrt(result);
}