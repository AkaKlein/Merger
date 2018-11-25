#include "row_vector.h"

#include "matrix.h"
#include "column_vector.h"

using namespace std;

RowVector::RowVector(int n)
    : m_data(n)
{
}

RowVector RowVector::operator+(RowVector const& other) const
{
    RowVector result(*this);
    result += other;
    return result;
}

RowVector& RowVector::operator+=(RowVector const& other)
{
    for (int i = 0; i < m_data.size(); ++i)
        m_data[i] += other.m_data[i];

    return *this;
}

RowVector RowVector::operator-(RowVector const& other) const
{
    RowVector result(*this);
    result -= other;
    return result;
}

RowVector& RowVector::operator-=(RowVector const& other)
{
    for (int i = 0; i < m_data.size(); ++i)
        m_data[i] -= other.m_data[i];

    return *this;
}

RowVector RowVector::operator*(Matrix const& other) const
{
    RowVector result(*this);
    result *= other;
    return result;
}

RowVector& RowVector::operator*=(Matrix const& other)
{
    RowVector result(other[0].size());
    for (int i = 0; i < other[0].size(); ++i)
    {
        result[i] = 0;
        for (int j = 0; j < m_data.size(); ++j)
            result[i] += m_data[j] * other[j][i];
    }
    
    m_data = result.m_data;
    return *this;
}

double RowVector::operator*(ColumnVector const& other) const
{
    double result = 0;
    for (int i = 0; i < m_data.size(); ++i)
        result += m_data[i] * other[i];

    return result;
}

RowVector RowVector::operator*(double other) const
{
    RowVector result(*this);
    result *= other;
    return result;
}

RowVector& RowVector::operator*=(double other)
{
    for (int i = 0; i < m_data.size(); ++i)
        m_data[i] *= other; 

    return *this;
}





