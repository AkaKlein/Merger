#pragma once

#include "Utils/algebra.h"

class LinearDemandsConstantCosts
{
public:
    LinearDemandsConstantCosts(ColumnVector const& income, ColumnVector const& costs, Matrix const& elasticities);

    ColumnVector ComputePrices() const;
    ColumnVector ComputeQuantities(ColumnVector const& prices) const;
    ColumnVector ComputeProfits(ColumnVector const& prices) const;
    ColumnVector ComputeConsumerWelfare(ColumnVector const& prices) const;
    void Merge(int i, int j);

private:
    ColumnVector m_a;
    ColumnVector m_c;
    Matrix m_B;
    Matrix m_D;
};
