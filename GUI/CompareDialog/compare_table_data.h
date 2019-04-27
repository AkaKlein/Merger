#pragma once

#include <memory>

#include <QAbstractTableModel>

#include "Models/model_interface.h"

class CompareTableData : public QAbstractTableModel
{
public:
    CompareTableData(std::shared_ptr<ModelInterface>& model1, std::shared_ptr<ModelInterface>& model2);

    virtual int rowCount(QModelIndex const& /*parent*/) const override final { return 5; }
    virtual int columnCount(QModelIndex const& parent) const override final;
    virtual QVariant data(QModelIndex const& index, int role) const override final;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override final;

private:
    void Initialize();

    std::shared_ptr<ModelInterface> m_model1;
    std::shared_ptr<ModelInterface> m_model2;

    ColumnVector m_diff_prices;
    ColumnVector m_diff_quantities;
    ColumnVector m_diff_costs;
    ColumnVector m_diff_profits;
    ColumnVector m_diff_consumer_welfare;
};
