#include "quadratic_demands_constant_costs.h"

#include <nlopt.hpp>

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
    return ColumnVector();

    nlopt::opt opt(nlopt::LD_MMA, m_a.Size());
    
    std::vector<double> lb(m_a.Size(), 0);
    opt.set_lower_bounds(lb);
    
    opt.set_min_objective(myfunc, NULL);


    // my_constraint_data data[2] = { {2,0}, {-1,1} };
    // opt.add_inequality_constraint(myconstraint, &data[0], 1e-8);
    // opt.add_inequality_constraint(myconstraint, &data[1], 1e-8);
    opt.set_xtol_rel(1e-4);

    std::vector<double> x(m_a.Size(), 1.0);
    double minimum;

    try
    {
        nlopt::result result = opt.optimize(x, minimum);
        ColumnVector prices(m_a.Size());
        for (std::size_t i = 0; i < prices.Size(); ++i)
            prices[i] = x[i];
        return result;
    }
    catch(std::exception &e) 
    {
        std::cout << "nlopt failed: " << e.what() << std::endl;
        return ColumnVector(m_a.Size());
    }
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
    return ColumnVector();
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