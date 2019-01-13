#pragma once

#include <memory>

#include <QDialog>
#include <QTableWidget>

#include "Models/model_interface.h"

class ModelResult : public QDialog
{
public:
    ModelResult(QWidget* parent, std::unique_ptr<ModelInterface> model, int model_index);

private:
    QTableWidget* m_table_widget;
};