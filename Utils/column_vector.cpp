#include "column_vector.h"

#include "matrix.h"
#include "row_vector.h"

using namespace std;

ColumnVector::ColumnVector(int n)
    : m_data(n)
{
}

ColumnVector ColumnVector::operator+(ColumnVector const& other) const
{
    ColumnVector result(*this);
    result += other;
    return result;
}

ColumnVector& ColumnVector::operator+=(ColumnVector const& other)
{
    for (int i = 0; i < m_data.size(); ++i)
        m_data[i] += other.m_data[i];

    return *this;
}

ColumnVector ColumnVector::operator-(ColumnVector const& other) const
{
    ColumnVector result(*this);
    result -= other;
    return result;
}

ColumnVector& ColumnVector::operator-=(ColumnVector const& other)
{
    for (int i = 0; i < m_data.size(); ++i)
        m_data[i] -= other.m_data[i];

    return *this;
}

ColumnVector ColumnVector::operator*(double other) const
{
    ColumnVector result(*this);
    result *= other;
    return result;
}

ColumnVector& ColumnVector::operator*=(double other)
{
    for (int i = 0; i < m_data.size(); ++ i)
        m_data[i] *= other;
    
    return *this;
}

ColumnVector ColumnVector::operator%(ColumnVector const& other) const
{
    ColumnVector result(*this);
    result %= other;
    return result;    
}

ColumnVector& ColumnVector::operator%=(ColumnVector const& other)
{
    for (int i = 0; i < m_data.size(); ++i)
       m_data[i] *= other[i]; 

    return *this;
}

std::ostream& operator<<(std::ostream& out, ColumnVector const& v)
{
    out << '(';
    for (int i = 0; i < v.Size(); ++i)
    {
        if (i != 0)
            out << ' ';
        out << v[i];
    }
    out << ')';
    return out;
}




