#pragma one

#include <vector>

class Matrix;
class RowVector;

class ColumnVector
{
public:
    ColumnVector(int n);


    int Size() const { return m_data.size(); }

    ColumnVector operator+(ColumnVector const& other) const;
    ColumnVector& operator+=(ColumnVector const& other);

    ColumnVector operator-(ColumnVector const& other) const;
    ColumnVector& operator-=(ColumnVector const& other);
    
    ColumnVector operator*(double other) const;
    ColumnVector& operator*=(double other);

    double& operator[](int index) { return m_data[index]; }
    double const& operator[](int index) const { return m_data[index]; }

private:
    std::vector<double> m_data;
};
