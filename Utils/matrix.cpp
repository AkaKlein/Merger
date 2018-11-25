#include "matrix.h"

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
    for (int i = 0; i < m_data.size(); ++i)
        for (int j = 0; j < m_data[i].size(); ++j)
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
    for (int i = 0; i < m_data.size(); ++i)
        for (int j = 0; j < m_data[i].size(); ++j)
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
    Matrix result(m_data.size(), other.m_data[0].size());
    for (int i = 0; i < m_data.size(); ++i)
    {
        for (int j = 0; j < other.m_data[0].size(); ++j)
        {
            result[i][j] = 0;
            for (int k = 0; k < m_data[0].size(); ++k)
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
    for (int i = 0; i < m_data.size(); ++ i)
        for (int j = 0; j < m_data[0].size(); ++j)
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
    for (int i = 0; i < m_data.size(); ++i)
        for (int j = 0; j < m_data[0].size(); ++j)
            m_data[i][j] *= other.m_data[i][j];

    return *this;
}

Matrix Matrix::Transpose() const
{
    Matrix result(m_data[0].size(), m_data.size());
    for (int i = 0; i < m_data.size(); ++i)
        for (int j = 0; j < m_data[0].size(); ++j)
            result[j][i] = m_data[i][j];

    return result;
}


