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
    for (int i = 0; i < Size(); ++i)
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
    for (int i = 0; i < Size(); ++i)
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
    RowVector result(other.Columns());
    for (int i = 0; i < other.Columns(); ++i)
    {
        result[i] = 0;
        for (int j = 0; j < Size(); ++j)
            result[i] += m_data[j] * other[j][i];
    }
    
    m_data = result.m_data;
    return *this;
}

double RowVector::operator*(ColumnVector const& other) const
{
    double result = 0;
    for (int i = 0; i < Size(); ++i)
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
    for (int i = 0; i < Size(); ++i)
        m_data[i] *= other; 

    return *this;
}

std::ostream& operator<<(std::ostream& out, RowVector const& v)
{
    int n = v.Size();
    out << n << endl;

    for (int i = 0; i < n; ++i)
    {
        if (i != 0)
            out << ' ';
        out << v[i];
    }
    out << endl;
    
    return out;
}

std::istream& operator>>(std::istream& in, RowVector& v)
{
    int n;
    in >> n;

    v = RowVector(n);
    for (int i = 0; i < n; ++i)
        in >> v[i];
    
    return in;
}
