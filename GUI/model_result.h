#pragma once

#include <memory>

#include <QDialog>
#include <QTableWidget>

#include "Models/model_interface.h"

class ModelResult : public QDialog
{
Q_OBJECT

public:
    ModelResult(QWidget* parent, std::unique_ptr<ModelInterface> model, int model_index);

private:
    void PopulateRow(int index, QString const& name, ColumnVector const& values);
    void AdjustTableSize();

    QTableWidget* m_table_widget;
};