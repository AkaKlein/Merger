#include "quadratic_demands_constant_costs.h"

#include <nlopt.hpp>

using namespace std;

double ForcePositiveQuantities(unsigned n, const double *x, double *grad, void *void_data)
{
    auto* data = static_cast<std::pair<QuadraticDemandsConstantCosts*, int>*>(void_data);
    QuadraticDemandsConstantCosts const& model = *data->first;
    int index = data->second;

    if (grad) 
    {
        for (unsigned k = 0; k < n; ++k)
            grad[k] = model.GetElasticities()[k][index] + 2 * model.GetQuadraticElasticities()[k][index] * x[k];
    }

    ColumnVector prices(n);
    for (int i = 0; i < prices.Size(); ++i)
        prices[i] = x[i];

    return -model.ComputeQuantities(prices)[index];
}

double ProfitPerFirm(unsigned n, const double *x, double *grad, void *void_data)
{
    auto* data = static_cast<std::pair<QuadraticDemandsConstantCosts*, std::vector<int>>*>(void_data);
    QuadraticDemandsConstantCosts const& model = *data->first;
    std::vector<int> const& firm_products = data->second;

    if (grad) 
    {
        // TODO:
        grad[0] = 0.0;
        grad[1] = 0.5 / sqrt(x[1]);
    }

    ColumnVector prices(n);
    for (int i = 0; i < prices.Size(); ++i)
        prices[i] = x[i];
    
    ColumnVector quantities = model.ComputeQuantities(prices);
    
    double res = 0;
    for (int j : firm_products)
        res += quantities[j] * (prices[j] - model.GetMarginalCosts()[j]);

    return res;
}

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

    std::vector<bool> seen(m_a.Size(), false);
    
    for (int i = 0; i < m_a.Size(); ++i)
    {
        if (seen[i])
            continue;

        std::vector<int> firm_products;
        for (int j = i; j < m_a.Size(); ++j)
        {
            if (AreProducedBySameFirm(i, j))
            {
                firm_products.push_back(j);
                seen[j] = true;
            }
        }

        nlopt::opt opt(nlopt::LD_MMA, m_a.Size());
        
        std::vector<double> lb(m_a.Size(), 0);
        opt.set_lower_bounds(lb);
        
        std::pair<QuadraticDemandsConstantCosts const*, std::vector<int>> func_data(this, firm_products);
        opt.set_min_objective(ProfitPerFirm, &func_data);

        for (int i = 0; i < m_a.Size(); ++i)
        {
            std::pair<QuadraticDemandsConstantCosts const*, int> data(this, i);
            opt.add_inequality_constraint(ForcePositiveQuantities, &data, 1e-8);
        }

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