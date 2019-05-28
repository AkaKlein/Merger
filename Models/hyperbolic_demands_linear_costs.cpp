#include "hyperbolic_demands_linear_costs.h"

using namespace std;

HyperbolicDemandsLinearCosts::HyperbolicDemandsLinearCosts(ColumnVector const& income, ColumnVector const& linear_costs, ColumnVector const& quadratic_costs, Matrix const& elasticities)
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

ColumnVector HyperbolicDemandsLinearCosts::ComputePrices() const
{
    // Construct a vector with the first order conditions functions of the profit.
    auto GetFOC = [this](ColumnVector const& p)
    {
        ColumnVector result(p.Size());
        for (int i = 0; i < p.Size(); ++i)
        {
            ColumnVector q = ComputeQuantities(p);
            result[i] = q[i];
            for (int j = 0; j < m_a.Size(); ++j)
            {
                double partial_q_j_partial_p_i = (-1) * m_B[j][i] * (1 / (p[i] * p[i]));
                result[i] += m_D[i][j] * ((p[j] - m_v[j] - m_w[j] * q[j]) * partial_q_j_partial_p_i - m_w[j] * q[j] * partial_q_j_partial_p_i); 
            }
        }
        return result;
    };

    // Construct a function to get the Jacobian matrix.
    auto GetJacobian = [this](ColumnVector const& p)
    {
        Matrix jacobian(m_a.Size(), m_a.Size());
        ColumnVector q = ComputeQuantities(p);

        for (int i = 0; i < m_a.Size(); ++i)
        {
            for (int j = 0; j < m_a.Size(); ++j)
            {
                double partial_q_i_partial_p_j = -m_B[i][j] * (1 / (p[j] * p[j]));
                double partial_q_j_partial_p_i = -m_B[j][i] * (1 / (p[i] * p[i]));
                jacobian[i][j] = partial_q_i_partial_p_j + m_D[i][j] * partial_q_j_partial_p_i;

                for (int k = 0; k < m_a.Size(); ++k)
                {
                    double partial_q_k_partial_p_j = (-1) * m_B[k][j] * (1 / (p[j] * p[j]));
                    double partial_q_k_partial_p_i = (-1) * m_B[k][i] * (1 / (p[i] * p[i]));
                    jacobian[i][j] -= 2 * (m_w[k] * m_D[i][k] * partial_q_k_partial_p_i * partial_q_k_partial_p_j);

                    if (i == j)
                    {
                        double partial2_q_k_partial2_p_i = 2 * m_B[k][i] * (1 / (p[i] * p[i] * p[i]));
                        jacobian[i][j] += m_D[i][k] * (p[k] - m_v[k] - m_w[k] * q[k]) * partial2_q_k_partial2_p_i;
                        jacobian[i][j] -= m_D[i][k] * (m_w[k] * q[k]) * partial2_q_k_partial2_p_i;
                    }
                }
            }
        }
        return jacobian;
    };

    // Initial prices.
    ColumnVector aux;
    ColumnVector p(m_a.Size());
    for (int i = 0; i < p.Size(); ++i)
        p[i] = 10;

    do
    {
        aux = p - GetJacobian(p).Inverse() * GetFOC(p);
        swap(p, aux);
    } while (norm(p - aux) > 1e-6);

    return p;
}

ColumnVector HyperbolicDemandsLinearCosts::ComputeQuantities(ColumnVector const& prices) const
{
    ColumnVector inverse_prices(prices.Size());
    for (int i = 0; i < prices.Size(); ++i)
    {
        inverse_prices[i] = 1 / prices[i];
    }
    return m_a + m_B * inverse_prices;
}

ColumnVector HyperbolicDemandsLinearCosts::ComputeCosts(ColumnVector const& quantities) const
{
    return m_v + m_w % quantities;
}

ColumnVector HyperbolicDemandsLinearCosts::ComputeProfits(ColumnVector const& prices) const
{
    ColumnVector q = ComputeQuantities(prices);
    return q % (prices - ComputeCosts(q));
}

ColumnVector HyperbolicDemandsLinearCosts::ComputeConsumerWelfare(ColumnVector const& prices) const
{
    return ColumnVector(m_a.Size());
}

void HyperbolicDemandsLinearCosts::Merge(int i, int j)
{
    m_D[i][j] = m_D[j][i] = 1;
}

bool HyperbolicDemandsLinearCosts::AreProducedBySameFirm(int i, int j) const
{
    return m_D[i][j];
}

void HyperbolicDemandsLinearCosts::SaveToFile(string const& file_path) const
{
    ofstream fout(file_path);

    fout << GetType() << " " << m_a << ' ' << m_v << ' ' << m_w << ' ' << m_B << ' ' << m_D << endl;
}

void HyperbolicDemandsLinearCosts::LoadFromFile(string const& file_path)
{
    ifstream fin(file_path);

    string type;
    fin >> type;
    if (type != ModelTypeToCompactString(GetType()))
        throw runtime_error("The model is not correct");
        
    fin >> m_a >> m_v >> m_w >> m_B >> m_D;
}

std::shared_ptr<ModelInterface> HyperbolicDemandsLinearCosts::Clone() const
{
    auto res = std::make_shared<HyperbolicDemandsLinearCosts>(m_a, m_v, m_w, m_B);
    res->m_D = m_D;
    return std::move(res);
}

std::shared_ptr<ModelInterface> HyperbolicDemandsLinearCosts::CloneWithoutMergers() const
{
    return std::make_shared<HyperbolicDemandsLinearCosts>(m_a, m_v, m_w, m_B);
}