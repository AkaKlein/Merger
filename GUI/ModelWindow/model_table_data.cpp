#include "model_table_data.h"

#include "Models/model_factory.h"

ModelTableData::ModelTableData(std::string const& file_path, ModelType model_type)
{ 
    m_model = ModelFactory::CreateModel(file_path, model_type);
    Initialize();
}

ModelTableData::ModelTableData(std::shared_ptr<ModelInterface>& model)
{
    m_model = std::move(model);
    Initialize();
}

void ModelTableData::Initialize()
{
    m_prices = m_model->ComputePrices();
    m_quantities = m_model->ComputeQuantities(m_prices);
    m_costs = m_model->ComputeCosts(m_quantities);
    m_profits = m_model->ComputeProfits(m_prices);
    m_consumer_welfare = m_model->ComputeConsumerWelfare(m_prices);
}

int ModelTableData::columnCount(QModelIndex const& /*parent*/) const
{
    return m_model->GetNumberOfProducts();
}

QVariant ModelTableData::data(QModelIndex const& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.row() == 0)
            return m_prices[index.column()];
        if (index.row() == 1)
            return m_quantities[index.column()];
        if (index.row() == 2)
            return m_costs[index.column()];
        if (index.row() == 3)
            return m_profits[index.column()];
        if (index.row() == 4)
            return m_consumer_welfare[index.column()];

        throw std::runtime_error("ModelTableData::data: should not happen");
    }

    return QVariant();
}

QVariant ModelTableData::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
            return tr("Product %1").arg(section + 1);
        
        if (section == 0)
            return tr("Prices");
        if (section == 1)
            return tr("Quantities");
        if (section == 2)
            return tr("Costs");
        if (section == 3)
            return tr("Profits");
        if (section == 4)
            return tr("Consumer Welfare");

        throw std::runtime_error("ModelTableData::headerData: should not happen");
    }

    return QVariant();
}