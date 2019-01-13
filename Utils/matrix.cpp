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

Matrix Matrix::Inverse() const
{
    int n = Rows();

    Matrix a(Rows(), 2 * Columns());
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            a[i][j] = m_data[i][j];

    for (int i = 0; i < n; ++i)
    {
        for (int j = n; j < 2 * n; ++j)
        {
            if (i == j - n)
                a[i][j] = 1;
            else
                a[i][j] = 0;
        }
    }

   for (int i = 0; i < n; ++i)
   {
        double t = a[i][i];
        for (int j = i; j < 2 * n; ++j)
            a[i][j] = a[i][j] / t;

        for (int j = 0; j < n; ++j)
        {
            if (i != j)
            {
                t = a[j][i];
                for (int k = 0; k < 2 * n; ++k)
                    a[j][k] = a[j][k] - t * a[i][k];
            }
        }
    }

    Matrix result(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = n; j < 2 * n; ++j)
            result[i][j - n] = a[i][j];

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
