#include "hyperbolic_demands_constant_costs.h"

using namespace std;

HyperbolicDemandsConstantCosts::HyperbolicDemandsConstantCosts(ColumnVector const& income, ColumnVector const& costs, Matrix const& elasticities)
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

ColumnVector HyperbolicDemandsConstantCosts::ComputePrices() const
{
    ColumnVector result;
    ColumnVector q = ComputeQuantities(result);
    for (int i = 0; i < prices.Size(); ++i)
    {
        for (int j = 0; j < m_a.Size(); ++j)
        {
            result[i] = ((p[i] - c[i]) * m_B[j][i] * m_D[j][i]) / q[j];
        }
    }


}

ColumnVector HyperbolicDemandsConstantCosts::ComputeQuantities(ColumnVector const& prices) const
{
    ColumnVector inverse_prices;
    for (int i = 0; i < prices.Size(), ++i)
    {
        inverse_prices[i] = 1 / prices[i];
    }
    return m_a + m_B * inverse_prices; 
}

ColumnVector HyperbolicDemandsConstantCosts::ComputeProfits(ColumnVector const& prices) const
{
    return ComputeQuantities(prices) % (prices - m_c);
}

ColumnVector HyperbolicDemandsConstantCosts::ComputeConsumerWelfare(ColumnVector const& prices) const
{
    return 0;
}

void HyperbolicDemandsConstantCosts::Merge(int i, int j)
{
    m_D[i][j] = m_D[j][i] = 1;
}

bool HyperbolicDemandsConstantCosts::AreProducedBySameFirm(int i, int j) const
{
    return m_D[i][j];
}

void HyperbolicDemandsConstantCosts::SaveToFile(string const& file_path) const
{
    ofstream fout(file_path);

    fout << GetType() << " " << m_a << ' ' << m_c << ' ' << m_B << ' ' << m_D << endl;
}

void HyperbolicDemandsConstantCosts::LoadFromFile(string const& file_path)
{
    ifstream fin(file_path);

    string type;
    fin >> type;
    if (type != ModelTypeToCompactString(GetType()))
        throw runtime_error("The model is not correct");
        
    fin >> m_a >> m_c >> m_B >> m_D;
}

std::shared_ptr<ModelInterface> HyperbolicDemandsConstantCosts::Clone() const
{
    auto res = std::make_shared<HyperbolicDemandsConstantCosts>(m_a, m_c, m_B);
    res->m_D = m_D;
    return std::move(res);
}

std::shared_ptr<ModelInterface> HyperbolicDemandsConstantCosts::CloneWithoutMergers() const
{
    return std::make_shared<HyperbolicDemandsConstantCosts>(m_a, m_c, m_B);
}