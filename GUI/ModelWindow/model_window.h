#pragma once

#include <memory>

#include <QMainWindow>

#include "Models/model_type.h"

class ModelTableView;

class ModelWindow : public QMainWindow
{
    Q_OBJECT

public:
    ModelWindow(QWidget* parent, std::string const& file_path, ModelType model_type, int model_index,
                std::vector<ModelWindow*>& model_windows);

private:
    virtual void closeEvent(QCloseEvent* event) override final;

    std::vector<ModelWindow*>& m_model_windows;

    ModelTableView* m_model_table_view;
};