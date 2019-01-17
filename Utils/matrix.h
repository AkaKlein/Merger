#pragma once

#include <fstream>
#include <vector>

class RowVector;
class ColumnVector;

/// Represents a matrix with real numbers.
class Matrix
{
public:
    /// Creates an empty matrix.
    Matrix() = default;

    /// Creates a matrix of @p n rows and @p m columns.
    ///
    /// @param n The number of rows.
    /// @param m The number of columns.
    Matrix(int n, int m);

    
    /*** Functions to request the size ***/

    /// Returns the number of rows of the matrix.
    int Rows() const { return m_data.size(); }

    /// Returns the number of columns of the matrix.
    int Columns() const { return m_data[0].size(); }


    /*** Operators ***/

    /// Adds the matrix @p other to this object and returns the resulting matrix.
    /// The object is left unchanged.
    ///
    /// @param other The matrix to be added to the object.
    Matrix operator+(Matrix const& other) const;

    /// Adds the matrix @p other into this object.
    ///
    /// @param other The matrix to be added to the object.
    Matrix& operator+=(Matrix const& other);

    /// Subtracts the matrix @p other to this object and returns the resulting matrix.
    /// The object is left unchanged.
    ///
    /// @param other The matrix to be subtracted to the object.
    Matrix operator-(Matrix const& other) const;

    /// Subtracts the matrix @p other into this object.
    ///
    /// @param other The matrix to be subtracted to the object.
    Matrix& operator-=(Matrix const& other);

    /// Multiplies the matrix @p other to this object and returns the resulting matrix.
    /// The object is left unchanged.
    ///
    /// @param other The matrix to be multiplied to the object.
    Matrix operator*(Matrix const& other) const;
    
    /// Multiplies the matrix @p other into this object.
    ///
    /// @param other The matrix to be multiplied to the object.
    Matrix& operator*=(Matrix const& other);

    /// Multiplies the real number @p other to this object and returns the resulting matrix.
    /// The object is left unchanged.
    ///
    /// @param other The real number to be multiplied to the object.
    Matrix operator*(double other) const;
    
    /// Multiplies the real number @p other into this object.
    ///
    /// @param other The real number to be multiplied to the object.
    Matrix& operator*=(double other);

    /// Applies the Hadamard product to the object and the matrix @p other and returns the resulting matrix.
    /// The object is left unchanges.
    ///
    /// @param other The matrix to be multiplied to the object.
    Matrix operator%(Matrix const& other) const;

    /// Applies the Hadamard product to the object and the matrix @p other and overwrites the current value of the object.
    ///
    /// @param other The matrix to be multiplied to the object.
    Matrix& operator%=(Matrix const& other);

    /// Returns the transposed matrix.
    Matrix Transpose() const;

    /// Returns the inverse matrix.
    Matrix Inverse() const;


    /*** Accessors ***/

    /// Returns the row of numbers indicated by @p row.
    ///
    /// @param row The index of the row.
    std::vector<double>& operator[](int row) { return m_data[row]; }

    /// Returns the row of numbers indicated by @p row.
    ///
    /// @param row The index of the row.
    std::vector<double> const& operator[](int row) const { return m_data[row]; }

private:
    /// Contains the numbers that form the matrix.
    std::vector<std::vector<double>> m_data;
};

std::ostream& operator <<(std::ostream& out, Matrix const& matrix);
std::istream& operator >>(std::istream& in, Matrix& matrix);