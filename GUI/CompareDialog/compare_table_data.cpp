#include "compare_table_data.h"

CompareTableData::CompareTableData(std::shared_ptr<ModelInterface>& model1, std::shared_ptr<ModelInterface>& model2)
{
    assert(model1->GetNumberOfProducts() == model2->GetNumberOfProducts());
    m_model1 = model1;
    m_model2 = model2;
    Initialize();
}

void CompareTableData::Initialize()
{
    ColumnVector prices1 = m_model1->ComputePrices();
    ColumnVector prices2 = m_model2->ComputePrices();
    ColumnVector quantities1 = m_model1->ComputeQuantities(prices1);
    ColumnVector quantities2 = m_model2->ComputeQuantities(prices2);

    m_diff_prices = prices1 - prices2;
    m_diff_quantities = quantities1 - quantities2;
    m_diff_costs = m_model1->ComputeCosts(quantities1) - m_model2->ComputeCosts(quantities2);
    m_diff_profits = m_model1->ComputeProfits(prices1) - m_model2->ComputeProfits(prices2);
    m_diff_consumer_welfare = m_model1->ComputeConsumerWelfare(prices1) - m_model2->ComputeConsumerWelfare(prices2);
}

int CompareTableData::columnCount(QModelIndex const& parent) const
{
    return m_model1->GetNumberOfProducts();
}

QVariant CompareTableData::data(QModelIndex const& index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (index.row() == 0)
            return m_diff_prices[index.column()];
        if (index.row() == 1)
            return m_diff_quantities[index.column()];
        if (index.row() == 2)
            return m_diff_costs[index.column()];
        if (index.row() == 3)
            return m_diff_profits[index.column()];
        if (index.row() == 4)
            return m_diff_consumer_welfare[index.column()];

        throw std::runtime_error("CompareTableData::data: should not happen");
    }

    return QVariant();
}

QVariant CompareTableData::headerData(int section, Qt::Orientation orientation, int role) const
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

        throw std::runtime_error("CompareTableData::headerData: should not happen");
    }

    return QVariant();
}