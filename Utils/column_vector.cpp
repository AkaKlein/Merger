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
    for (int i = 0; i < Size(); ++i)
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
    for (int i = 0; i < Size(); ++i)
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
    for (int i = 0; i < Size(); ++ i)
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
    for (int i = 0; i < Size(); ++i)
       m_data[i] *= other[i]; 

    return *this;
}

std::ostream& operator<<(std::ostream& out, ColumnVector const& v)
{
    int n = v.Size();
    out << n << endl;

    for (int i = 0; i < n; ++i)
        out << v[i] << endl;
    
    return out;
}

std::istream& operator>>(std::istream& in, ColumnVector& v)
{
    int n;
    in >> n;

    v = ColumnVector(n);
    for (int i = 0; i < n; ++i)
        in >> v[i];
    
    return in;
}