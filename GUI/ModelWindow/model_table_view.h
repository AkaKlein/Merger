#pragma once

#include <memory>

#include "GUI/Common/base_table_view.h"
#include "Models/model_type.h"

class ModelInterface;
class ModelTableData;

class ModelTableView : public BaseTableView
{
public:
    ModelTableView(QWidget* parent, std::string const& file_path, ModelType model_type);
    ModelTableView(QWidget* parent, std::shared_ptr<ModelInterface>& model);

private:
    ModelTableData* m_data;
};