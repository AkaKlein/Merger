#include "quadratic_demands_constant_costs.h"

using namespace std;

QuadraticDemandsConstantCosts::QuadraticDemandsConstantCosts(ColumnVector const& income, ColumnVector const& costs, Matrix const& elasticities, Matrix const& quad_elasticities)
    : m_a(income), m_c(costs), m_B(elasticities), m_E(quad_elasticities), m_D(elasticities.Rows(), elasticities.Columns())
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

ColumnVector QuadraticDemandsConstantCosts::ComputePrices() const
{
    // Construct a vector with the first order conditions functions of the profit.
    auto GetFOC = [this](ColumnVector const& p)
    {
        ColumnVector result(p.Size());
        for (int i = 0; i < p.Size(); ++i)
        {
            result[i] = ComputeQuantities(p)[i];
            for (int j = 0; j < m_a.Size(); ++j)
            {
                double partial_q_j_partial_p_i = m_B[j][i] + 2 * m_E[j][i] * p[i];
                result[i] += m_D[i][j] * (p[j] - m_c[j]) * partial_q_j_partial_p_i;
            }
        }
        return result;
    };

    // Construct a function to get the Jacobian matrix.
    auto GetJacobian = [this](ColumnVector const& p)
    {
        Matrix jacobian(m_a.Size(), m_a.Size());
        for (int i = 0; i < m_a.Size(); ++i)
        {
            for (int j = 0; j < m_a.Size(); ++j)
            {
                double partial_q_i_partial_p_j = m_B[i][j] + 2 * m_E[i][j] * p[j];
                double partial_q_j_partial_p_i = m_B[j][i] + 2 * m_E[j][i] * p[i];
                jacobian[i][j] = partial_q_i_partial_p_j + m_D[i][j] * partial_q_j_partial_p_i;
                if (i == j)
                {
                    for (int k = 0; k < m_a.Size(); ++k)
                    {
                        double partial2_q_k_partial2_p_i = 2 * m_E[k][i];
                        jacobian[i][j] += m_D[i][k] * (p[k] - m_c[k]) * partial2_q_k_partial2_p_i;
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
        p[i] = 0;

    do
    {
        aux = p - GetJacobian(p).Inverse() * GetFOC(p);
        swap(p, aux);
    } while (norm(p - aux) > 1e-6);

    return p;
}

ColumnVector QuadraticDemandsConstantCosts::ComputeQuantities(ColumnVector const& prices) const
{
    return m_a + m_B.Transpose() * prices + m_E.Transpose() * (prices % prices);
}

ColumnVector QuadraticDemandsConstantCosts::ComputeProfits(ColumnVector const& prices) const
{
    return ComputeQuantities(prices) % (prices - m_c);
}

ColumnVector QuadraticDemandsConstantCosts::ComputeConsumerWelfare(ColumnVector const& prices) const
{
    return ColumnVector(m_a.Size());
}

void QuadraticDemandsConstantCosts::Merge(int i, int j)
{
    m_D[i][j] = m_D[j][i] = 1;
}

bool QuadraticDemandsConstantCosts::AreProducedBySameFirm(int i, int j) const
{
    return m_D[i][j];
}

void QuadraticDemandsConstantCosts::SaveToFile(string const& file_path) const
{
    ofstream fout(file_path);

    fout << GetType() << " " << m_a << ' ' << m_c << ' ' << m_B << ' ' << m_E << ' ' << m_D << endl;
}

void QuadraticDemandsConstantCosts::LoadFromFile(string const& file_path)
{
    ifstream fin(file_path);

    string type;
    fin >> type;
    if (type != ModelTypeToCompactString(GetType()))
        throw runtime_error("The model is not correct");
        
    fin >> m_a >> m_c >> m_B >> m_E >> m_D;
}

std::shared_ptr<ModelInterface> QuadraticDemandsConstantCosts::Clone() const
{
    auto res = std::make_shared<QuadraticDemandsConstantCosts>(m_a, m_c, m_B, m_E);
    res->m_D = m_D;
    return std::move(res);
}

std::shared_ptr<ModelInterface> QuadraticDemandsConstantCosts::CloneWithoutMergers() const
{
    return std::make_shared<QuadraticDemandsConstantCosts>(m_a, m_c, m_B, m_E);
}