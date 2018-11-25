#include "linear_demands_constant_costs.h"

using namespace std;

LinearDemandsConstantCosts::LinearDemandsConstantCosts(ColumnVector const& income, ColumnVector const& costs, Matrix const& elasticities)
    : m_a(income), m_c(costs), m_B(elasticities), m_D(elasticities.Rows(), elasticities.Columns())
{
    for (int i = 0; i < m_D.Rows(); ++i)
    {
        for (int j = 0; j < m_D.Columns(); ++j)
        {
            if (i == j)
                m_D[i][j] = 1;
            else 
                m_D[i][j] = 0;
        }
    }
}

ColumnVector LinearDemandsConstantCosts::ComputePrices() const
{
    return (m_B.Transpose() + m_D % m_B).Inverse() * ((m_D % m_B) * m_c - m_a);
}

ColumnVector LinearDemandsConstantCosts::ComputeQuantities(ColumnVector const& prices) const
{
    return m_a + m_B * prices;
}

ColumnVector LinearDemandsConstantCosts::ComputeProfits(ColumnVector const& prices) const
{
    return ComputeQuantities(prices) % (prices - m_c);
}

ColumnVector LinearDemandsConstantCosts::ComputeConsumerWelfare(ColumnVector const& prices) const
{
    ColumnVector diagonal(Diagonal(m_B));
    ColumnVector neg_diag_inv(m_B.Rows());
    for (int i = 0; i < m_B.Rows(); ++i)
        neg_diag_inv[i] = -1 / diagonal[i];

    return ComputeQuantities(prices) % ((m_a + m_B * prices) % neg_diag_inv) * 0.5;
}
