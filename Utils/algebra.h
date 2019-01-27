#pragma once

#include "column_vector.h"
#include "matrix.h"
#include "row_vector.h"

ColumnVector operator*(Matrix const& m, ColumnVector const& v);

Matrix operator*(ColumnVector const& c, RowVector const& r);

ColumnVector Transpose(RowVector const& v);

RowVector Transpose(ColumnVector const& v);

Matrix operator*(double k, Matrix const& matrix);

ColumnVector operator*(double k, ColumnVector const& v);

RowVector operator*(double k, RowVector const& v);

ColumnVector Diagonal(Matrix const& matrix);

Matrix operator%(ColumnVector const& v, Matrix const& m);

Matrix operator%(Matrix const& m, ColumnVector const& v);
