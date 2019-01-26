#pragma once

#include <memory>

#include "GUI/Common/base_table_view.h"
#include "Models/model_type.h"

class ModelInterface;
class CompareTableData;

class CompareTableView : public BaseTableView
{
public:
    CompareTableView(QWidget* parent, std::shared_ptr<ModelInterface>& model1, std::shared_ptr<ModelInterface>& model2);

private:
    CompareTableData* m_data;
};