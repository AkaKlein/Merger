#pragma one

#include <vector>

class Matrix;
class ColumnVector;

class RowVector
{
public:
    RowVector(int n);


    int Size() const { return m_data.size(); }

    RowVector operator+(RowVector const& other) const;
    RowVector& operator+=(RowVector const& other);

    RowVector operator-(RowVector const& other) const;
    RowVector& operator-=(RowVector const& other);

    RowVector operator*(Matrix const& other) const;
    RowVector& operator*=(Matrix const& other);
    
    double operator*(ColumnVector const& other) const;

    RowVector operator*(double other) const;
    RowVector& operator*=(double other);

    double& operator[](int index) { return m_data[index]; }
    double const& operator[](int index) const { return m_data[index]; }

private:
    std::vector<double> m_data;
};
