#include "linear_demands_linear_costs.h"

using namespace std;

LinearDemandsLinearCosts::LinearDemandsLinearCosts(ColumnVector const& income, ColumnVector const& linear_costs, ColumnVector const& quadratic_costs, 
                                                   Matrix const& elasticities)
    : m_a(income), m_v(linear_costs), m_w(quadratic_costs), m_B(elasticities), m_D(elasticities.Rows(), elasticities.Columns())
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

ColumnVector LinearDemandsLinearCosts::ComputePrices() const
{
    return (m_B.Transpose() + m_D % m_B - 2 * (m_D % m_B) * (m_w % m_B.Transpose())).Inverse() * ((m_D % m_B) * m_v + 2 * (m_D % m_B) * (m_w % m_a) - m_a);
}

ColumnVector LinearDemandsLinearCosts::ComputeQuantities(ColumnVector const& prices) const
{
    return m_a + m_B.Transpose() * prices;
}

ColumnVector LinearDemandsLinearCosts::ComputeCosts(ColumnVector const& quantities) const
{
    return m_v + m_w % quantities;
}

ColumnVector LinearDemandsLinearCosts::ComputeProfits(ColumnVector const& prices) const
{
    ColumnVector q = ComputeQuantities(prices);
    return q % (prices - m_v - m_w % q);
}

ColumnVector LinearDemandsLinearCosts::ComputeConsumerWelfare(ColumnVector const& prices) const
{
    ColumnVector diagonal(Diagonal(m_B));
    ColumnVector neg_diag_inv(m_B.Rows());
    for (int i = 0; i < m_B.Rows(); ++i)
        neg_diag_inv[i] = -1 / diagonal[i];

    return ComputeQuantities(prices) % ((m_a + m_B * prices) % neg_diag_inv) * 0.5;
}

void LinearDemandsLinearCosts::Merge(int i, int j)
{
    m_D[i][j] = m_D[j][i] = 1;
}

bool LinearDemandsLinearCosts::AreProducedBySameFirm(int i, int j) const
{
    return m_D[i][j];
}

void LinearDemandsLinearCosts::SaveToFile(string const& file_path) const
{
    ofstream fout(file_path);

    fout << GetType() << " " << m_a << ' ' << m_v << ' ' << m_w << ' ' << m_B << ' ' << m_D << endl;
}

void LinearDemandsLinearCosts::LoadFromFile(string const& file_path)
{
    ifstream fin(file_path);

    string type;
    fin >> type;
    if (type != ModelTypeToCompactString(GetType()))
        throw runtime_error("The model is not correct");
        
    fin >> m_a >> m_v >> m_w >> m_B >> m_D;
}

std::shared_ptr<ModelInterface> LinearDemandsLinearCosts::Clone() const
{
    auto res = std::make_shared<LinearDemandsLinearCosts>(m_a, m_v, m_w, m_B);
    res->m_D = m_D;
    return std::move(res);
}

std::shared_ptr<ModelInterface> LinearDemandsLinearCosts::CloneWithoutMergers() const
{
    return std::make_shared<LinearDemandsLinearCosts>(m_a, m_v, m_w, m_B);
}