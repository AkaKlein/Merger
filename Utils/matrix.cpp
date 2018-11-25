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
    /*int n = Rows();


    for(int i = 0; i < n; ++i)
    {
        for(int j = n; j < 2*n; ++j)
        {
            if (i == j - n)
                a[i][j]  = 1;
            else
                a[i][j] = 0;
        }
    }

   for(i=0;i<n;i++)
   {
      t=a[i][i];
      for(j=i;j<2*n;j++)
          a[i][j]=a[i][j]/t;
      for(j=0;j<n;j++)
      {
         if(i!=j)
         {
            t=a[j][i];
            for(k=0;k<2*n;k++)
                a[j][k]=a[j][k]-t*a[i][k];
          }
      }
   }
   cout<<"\n\nInverse matrix\n\n";
   for(i=0;i<n;i++)
   {
      for(j=n;j<2*n;j++)
         cout<<"\t"<<a[i][j];
      cout<<"\n";
    }
    */
}