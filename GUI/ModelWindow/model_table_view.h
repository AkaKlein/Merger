#pragma once

#include <memory>

#include <QTableView>

#include "Models/model_type.h"

class ModelInterface;
class ModelTableData;

class ModelTableView : public QTableView
{
public:
    ModelTableView(QWidget* parent, std::string const& file_path, ModelType model_type);
    ModelTableView(QWidget* parent, std::shared_ptr<ModelInterface>& model);

protected:
    virtual void keyPressEvent(QKeyEvent* event) override final;
    virtual QSize sizeHint() const override final;

private:
    ModelTableData* m_data;
};