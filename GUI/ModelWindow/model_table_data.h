#pragma once

#include <memory>

#include <QAbstractTableModel>

#include "Models/model_interface.h"

class ModelTableData : public QAbstractTableModel
{
public:
    ModelTableData(std::string const& file_path, ModelType model_type);
    ModelTableData(std::shared_ptr<ModelInterface>& model);

    ModelInterface const& GetModel() const { return *m_model; }

    virtual int rowCount(QModelIndex const& parent) const override final { return 5; }
    virtual int columnCount(QModelIndex const& parent) const override final;
    virtual QVariant data(QModelIndex const& index, int role) const override final;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override final;

private:
    void Initialize();

    std::shared_ptr<ModelInterface> m_model;

    ColumnVector m_prices;
    ColumnVector m_quantities;
    ColumnVector m_costs;
    ColumnVector m_profits;
    ColumnVector m_consumer_welfare;
};
